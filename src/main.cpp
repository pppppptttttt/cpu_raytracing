#include "renderer/renderer.h"

int main()
{
    renderer Rnd(400, 400);
    Rnd.Init(core_type::SDL);
    //Rnd.Cam.Set({0}, {0, 0, 0}, 90.0);
    Rnd.SamplesPerPixel = 3;
    Rnd.MaxDepth = 50;
    // Rnd.Cam.Set(point3(0.2, 0.35, 1) * 4, {0, 0.35, 0}, 60);
    lambertian ground({0.2, 0.5, 0.5});
    // lambertian center({0.7, 0.7, 0.3});
    metal left({0.8, 0, 0.8}, 0.4);
    lambertian center({0.8, 0.8, 0.8});
    metal right({0, 0, 0.8}, 0.1);
    metal building({0.8, 0.47, 0.30}, 0.0);
    // lambertian teapot({0, 0.8, 0});
    Rnd // << std::make_shared<model>("bin/low_buildingA.obj", &building)
        << std::make_shared<sphere>(point3(0, 0, -1), 0.5, &left)
        << std::make_shared<sphere>(point3(0, -100.5, -1), 100, &ground)
        // << std::make_shared<sphere>(point3(-1, 0.5, -1), 0.5, &left)
        // << std::make_shared<sphere>(point3(1, 0.5, -1), 0.5, &right)
    ;
    auto Frame = Rnd.RenderFrame();
    Frame->SavePPM("teapot.ppm");
    Rnd.MainLoop();
    return 0;
}