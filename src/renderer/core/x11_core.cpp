#include "x11_core.h"

void x11_core::Init( uint32_t Width, uint32_t Height )
{
    Dp = XOpenDisplay(getenv("DISPLAY"));
    assert(Dp != NULL);
    Screen = DefaultScreen(Dp);
    Window ro = DefaultRootWindow(Dp);
    Wnd = XCreateSimpleWindow(Dp, ro, 0, 0, Width, Height, 1, 
                              BlackPixel(Dp, Screen), WhitePixel(Dp, Screen));
    XMapWindow(Dp, Wnd); //Make window visible
    XStoreName(Dp, Wnd, "X11 based RT"); // Set window title
    //Prepare the window for drawing
    Ctx = XCreateGC(Dp, ro, 0, NULL);

    W = Width, H = Height;
    Buffer = new u_long[W * H];
}

void x11_core::PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& c )
{
    if (x < W && y < H)
    {
        Buffer[y * W + x] = c[2] + (c[1] << 8) + (c[0] << 16);
        // XSetForeground(Dp, Ctx, Buffer[y * W + x]);
        // XDrawPoint(Dp, Wnd, Ctx, x, y);
    }
}

void x11_core::DrawBuffer()
{
    for (uint32_t y = 0; y < H; y++)
        for (uint32_t x = 0; x < W; x++)
        {
            XSetForeground(Dp, Ctx, Buffer[y * W + x]);
            XDrawPoint(Dp, Wnd, Ctx, x, y);
        }
}

void x11_core::Render()
{
   DrawBuffer();
}

void x11_core::Close()
{
    delete[] Buffer;
    XFreeGC(Dp, Ctx);
    XDestroyWindow(Dp, Wnd);
    XCloseDisplay(Dp);
}

void x11_core::MainLoop()
{
    bool running = true;
    XSelectInput(Dp, Wnd, ExposureMask | KeyPressMask);
    XEvent ev;
    while (running)
    {
        XNextEvent(Dp, &ev);
        switch (ev.type)
        {
        case Expose:
            Render();
            break;

        case KeyPress:
            if (XLookupKeysym(&ev.xkey, 0) == XK_Escape)
                running = false;
            break;

        default:
            break;
        }
    }
}