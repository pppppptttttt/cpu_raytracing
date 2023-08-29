# cpu_raytracing

## Features
- Antialiasing
- Multithreading
- Loading models from .obj file
- Rendering image to .ppm and/or displaying it on screen

## Dependencies

Guess you will need to install sdl2 and X11 libs; or just edit some code about core and render .ppm images(set core type to "Default"):

 - sudo apt-get install libsdl2-dev
 - sudo apt-get install libx11-dev
## Current shots
![frame5](https://github.com/pppppptttttt/cpu_raytracing/assets/140364764/ada468b1-95b3-4d1b-8059-a0b0f17235de)
![frame7](https://github.com/pppppptttttt/cpu_raytracing/assets/140364764/f6e6779c-ea69-4df3-ac4a-aa08a8641948)
![frame9](https://github.com/pppppptttttt/cpu_raytracing/assets/140364764/86c4446e-0d2c-4c7d-9320-245c9cdcfa26)
![teapot](https://github.com/pppppptttttt/cpu_raytracing/assets/140364764/20bb9d7e-51a8-4133-8be9-8059594b071d)

## TODO
 - Change AA to something faster(like adaptive supersampling)
 - Textures from images and solid textures(noise etc.)
 - Physically based lights(objects that emits light on scene)
 - Fix models ligthing, last frame looks strange
