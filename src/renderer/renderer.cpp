#include "renderer.h"
#include <cstdio>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

void renderer::Init( core_type T )
{
    switch(T)
    {
    case core_type::Default:
        RenderCore = std::make_unique<core>();
        break;
    case core_type::SDL:
        RenderCore = std::make_unique<sdl_core>();
        break;
    case core_type::X11:
        RenderCore = std::make_unique<x11_core>();
        break;
    default:
        break;
    }
    RenderCore->Init(WIDTH, HEIGHT);
}

renderer::~renderer()
{
    RenderCore->Close();
}

renderer& renderer::AddShp( std::shared_ptr<shape> Shp )
{
    Scene.push_back(Shp);
    return *this;
}

bool scene::HasIntersection( const ray& R, hit_info& Info ) const
{
    bool hits = false;
    hit_info CurrentHit {{}, {}, 1e9};

    for (const auto& shp : *this)
        if (shp->Hits(R, CurrentHit) && CurrentHit.t < Info.t && CurrentHit.t > THR)
        {
            Info = CurrentHit;
            hits = true;
        }
    return hits;
}

color3 scene::Shade( const ray& R, uint32_t depth ) const
{
    hit_info Info {{}, {}, 1e9};
    if (depth > 0 && HasIntersection(R, Info))
    {
        ray scattered;
        color3 attenuation;
        if (Info.mtl->Scatter(R, Info, attenuation, scattered))
        {
            ray r = scattered;
            r.Origin += mth::random_unit_vector<double>() * THR;
            return attenuation * Shade(r, depth - 1);
        }
        return color3(0);
    }
    return color3(0.3, 0.47, 0.8);
}

std::shared_ptr<image> renderer::RenderFrame()
{
    constexpr auto fixedc =
        []( const color3& c ) -> mth::vec3<u_char>
        {
            for (uint32_t i = 0; i < 3; i++)
                std::clamp(c[i], 0.0, 1.0);
            return mth::vec3<u_char>(static_cast<u_char>(sqrt(c[0]) * 255.0),
                                     static_cast<u_char>(sqrt(c[1]) * 255.0),
                                     static_cast<u_char>(sqrt(c[2]) * 255.0));
        };

    auto Frame = std::make_shared<image>(WIDTH, HEIGHT);

    uint32_t progress_bar_w = 50;
    std::cout << "Rendering frame..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    const uint32_t cores_n = std::thread::hardware_concurrency()-4;
    //cores_n = 1;
    std::vector<std::thread> shaders(cores_n);
    std::mutex cout_lock;
    std::atomic<uint32_t> p(0);

    for (uint32_t i = 0; i < cores_n; i++)
        shaders[i] = std::thread(
            [&, i]()
            {
                for (uint32_t y = i; y <= HEIGHT; y += cores_n)
                    for (uint32_t x = 0; x <= WIDTH; x++)
                    {
                        color3 c(0);
                        for (uint32_t _ = 0; _ < SamplesPerPixel; _++)
                        {
                            ray r = Cam.GetThresholdedRay(x, y);
                            c += Scene.Shade(r, MaxDepth);
                        }
                        c /= static_cast<double>(SamplesPerPixel);
                        Frame->PutPixel(x, y, fixedc(c));
                        RenderCore->PutPixel(x, y, fixedc(c));
                        p.fetch_add(1, std::memory_order_relaxed);
                    }
            });

    while (p < WIDTH * HEIGHT)
    {
        std::cout << "[";
        for (uint32_t _ = 0; _ < progress_bar_w; _++)
            if (_ < static_cast<double>(p) / WIDTH / HEIGHT * progress_bar_w) std::cout << "#";
            else std::cout << " ";
        std::cout << "]" << ceil(static_cast<double>(p) / WIDTH / HEIGHT * 100.0) << "%\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    for (uint32_t i = 0; i < cores_n; i++)
        shaders[i].join();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << std::endl << "Done" << std::endl << "Elapsed time: " << elapsed.count() / 1000.0  << "s" << std::endl;
    return Frame;
}

void renderer::MainLoop()
{
    RenderCore->MainLoop();
}

void image::SavePPM( const std::string& fn ) const
{
    FILE* f = fopen(fn.c_str(), "wb");
    if (!f)
    {
        std::cout << "lol...\n";
        return;
    }
    fprintf(f, "P6\n%d %d\n255\n", W, H);
    fwrite(Buffer.data(), 3 * W * H * sizeof(Buffer[0]), 1, f);
    fclose(f);
}