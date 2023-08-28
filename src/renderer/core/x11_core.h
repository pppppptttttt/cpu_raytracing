#pragma once
#include "core.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

class x11_core : public core
{
public:
    void Init( uint32_t Width, uint32_t Height ) override;
    void Close() override;
    void PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& color ) override;
    void Render() override;
    void MainLoop() override;
private:
    void DrawBuffer();
    u_long* Buffer;
    Display* Dp;
    Window Wnd;
    GC Ctx;
    uint32_t Screen, W, H;
};