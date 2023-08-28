#include "renderer/renderer.h"

int main()
{
    renderer Rnd(1920, 1080);
    Rnd.Init(core_type::X11);
    Rnd.Cam.Set({0}, {0, 0, 0}, 150.0);
    Rnd.SamplesPerPixel = 300;
    Rnd.MaxDepth = 50;
    Rnd.Cam.Set(point3(0.2, 0.8, 1) * 2, {0, 0, 0}, 90);
    lambertian ground({0.2, 0.5, 0.5});
    // lambertian center({0.7, 0.7, 0.3});
    metal left({0.8, 0, 0.8}, 0.1);
    lambertian center({0.8, 0.8, 0.8});
    metal right({0, 0, 0.8}, 0.1);
    metal teapot({0, 0.8, 0}, 0.0);
    Rnd << std::make_shared<model>("bin/teapot.obj", &teapot)
        //<< std::make_shared<sphere>(point3(0, 0, -1), 0.5, &center)
        << std::make_shared<sphere>(point3(0, -100.5, -1), 100, &ground)
        << std::make_shared<sphere>(point3(-1, 0, -1), 0.5, &left)
        << std::make_shared<sphere>(point3(1, 0, -1), 0.5, &right)
    // Rnd << std::make_shared<triangle>(point3(0, 1, -1), point3(-0.5, 0, -1), point3(0.5, 0, -1), &right)
    // Rnd << std::make_shared<model>("bin/box.obj", &left)
    // Rnd << std::make_shared<sphere>(point3(-1, 1, 0), 0.5, &ground)
    ;
    auto Frame = Rnd.RenderFrame();
    Frame->SavePPM("frames/frame8.ppm");
    Rnd.MainLoop();
    return 0;
}