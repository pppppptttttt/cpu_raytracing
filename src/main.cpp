#include "renderer/renderer.h"

int main()
{
    scene Scene;
    const uint32_t scene_no = 2;

    renderer Rnd(1920, 1080);
    Rnd.Init(core_type::SDL);
    Rnd.Cam.Set({-2, 0, 4}, {0, 0, -1}, 20.0);
    Rnd.SamplesPerPixel = 1;
    Rnd.MaxDepth = 50;

    switch(scene_no)
    {
    case 0:
        {
            auto ground = std::make_shared<lambertian>(vec3(0.2, 0.5, 0.5));
            auto left = std::make_shared<metal>(vec3(0.8, 0, 0.8), 0.4);
            auto center = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.8));
            auto right = std::make_shared<metal>(vec3(0, 0, 0.8), 0.1);
            Scene << std::make_shared<sphere>(point3(0, 0, -1), 0.5, center)
                  << std::make_shared<sphere>(point3(0, -100.5, -1), 100, ground)
                  << std::make_shared<sphere>(point3(-1, 0, -1), 0.5, left)
                  << std::make_shared<sphere>(point3(1, 0, -1), 0.5, right);
        }
        break;
    case 1:
        {
            Rnd.Cam.Set(point3(0.2, 0.35, 1) * 4, {0, 0.35, 0}, 60);
            auto building = std::make_shared<metal>(vec3(0.8, 0.47, 0.30), 0.0);
            auto ground = std::make_shared<lambertian>(vec3(0.2, 0.5, 0.5));
            auto left = std::make_shared<metal>(vec3(0.8, 0, 0.8), 0.4);
            auto right = std::make_shared<metal>(vec3(0, 0, 0.8), 0.1);
            Scene << std::make_shared<model>("bin/low_buildingA.obj", building)
                  << std::make_shared<sphere>(point3(0, -100, 0), 100, ground)
                  << std::make_shared<sphere>(point3(-1, 0.5, -1), 0.8, left)
                  << std::make_shared<sphere>(point3(1, 0.5, -1), 0.7, right);
        }
        break;
    case 2:
        {
            auto ground = std::make_shared<lambertian>(vec3(0.2, 0.5, 0.5));
            auto left = std::make_shared<dielectric>(vec3(1.0, 0.4, 1.0), 1.5);
            auto center = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.8));
            auto right = std::make_shared<metal>(vec3(0, 0, 0.8), 0.1);
            Scene << std::make_shared<sphere>(point3(0, 0, -1), 0.5, center)
                  << std::make_shared<sphere>(point3(0, -100.5, -1), 100, ground)
                  << std::make_shared<sphere>(point3(-1, 0, -1), 0.5, left)
                  << std::make_shared<sphere>(point3(1, 0, -1), 0.5, right);
        }
        break;
    }

    auto Frame = Rnd.RenderFrame(Scene);
    Frame->SavePPM("glass.ppm");
    Rnd.MainLoop();
    return 0;
}