#include "sdl_core.h"

void sdl_core::Init( uint32_t Width, uint32_t Height )
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(Width, Height, 0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    Buffer.resize(Height);
    for (auto& v : Buffer)
        v.resize(Width);
}

void sdl_core::Close()
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void sdl_core::PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& color )
{
    if (y >= 0 && y < Buffer.size() && x >= 0 && x < Buffer[0].size())
        Buffer[y][x] = color;
}

void sdl_core::DrawBuffer()
{
    for (uint32_t y = 0; y < Buffer.size(); y++)
        for (uint32_t x = 0; x < Buffer[y].size(); x++)
        {
            SDL_SetRenderDrawColor(Renderer, Buffer[y][x][0], Buffer[y][x][1], Buffer[y][x][2], 1);
            SDL_RenderDrawPoint(Renderer, x, y);
        }
}

void sdl_core::Render()
{
    DrawBuffer();
    SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
}

void sdl_core::MainLoop()
{
    Render();
    SDL_Event ev;
    while (true)
    {
        SDL_PollEvent(&ev);
        switch (ev.type)
        {
        case SDL_QUIT:
            return;
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return;
            }
            break;
        default:
            break;
        }
    }
}
