#include "sdl_core.h"

void sdl_core::Init( uint32_t Width, uint32_t Height )
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(Width, Height, 0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
}

void sdl_core::Close()
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void sdl_core::PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& color )
{
    SDL_SetRenderDrawColor(Renderer, color.x, color.y, color.z, 1);
    SDL_RenderDrawPoint(Renderer, x, y);
    // SDL_RenderPresent(Renderer);
}

void sdl_core::Render()
{
    SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_Event e;
    while (true)
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
            break;
}
