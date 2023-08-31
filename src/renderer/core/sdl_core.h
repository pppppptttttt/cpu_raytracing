#pragma once
#include "core.h"
#include <SDL2/SDL.h>

class sdl_core : public core
{
public:
    void Init( uint32_t Width, uint32_t Height ) override;
    void Close() override;
    void PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& color ) override;
    void Render() override;
    void MainLoop() override;
private:
    void DrawBuffer();
    std::vector<std::vector<mth::vec3<u_char>>> Buffer;
    SDL_Window* Window;
    SDL_Renderer* Renderer;
};
