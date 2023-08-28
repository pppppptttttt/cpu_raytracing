#pragma once
#include <vector>
#include "core/cores.h"
#include "shapes/shapes.h"

class scene : public std::vector<std::shared_ptr<shape>>
{
public:
    color3 Shade( const ray& R, uint32_t depth ) const;
private:
    bool HasIntersection( const ray& R, hit_info& Info ) const;
};

class image
{
public:
    image( uint32_t w, uint32_t h ) : W(w), H(h) { Buffer.resize(3 * W * H); }
    inline image& PutPixel( uint32_t x, uint32_t y, const mth::vec3<u_char>& c )
    {
        if (x < W && y < H)
        {
            Buffer[3 * (y * W + x)] = c[0];
            Buffer[3 * (y * W + x) + 1] = c[1];
            Buffer[3 * (y * W + x) + 2] = c[2];
        }
        return *this;
    }
    void SavePPM( const std::string& fn ) const;
private:
    std::vector<u_char> Buffer;
    uint32_t W = 0, H = 0;
};

enum class core_type
{
    Default = 0, SDL = 1, X11 = 2
};

class renderer
{
public:
    renderer( uint32_t W = 1000, uint32_t H = 800 ) : Cam(W, H), WIDTH(W), HEIGHT(H) {}
    void Init( core_type T = core_type::Default );
    std::shared_ptr<image> RenderFrame();
    renderer& AddShp( std::shared_ptr<shape> Shp );
    inline renderer& operator<<( std::shared_ptr<shape> Shp ) { AddShp(Shp); return *this; }
    void MainLoop();
    ~renderer();

    camera Cam;
    uint32_t SamplesPerPixel = 1;
    uint32_t MaxDepth = 5;
private:
    std::unique_ptr<core> RenderCore;
    const uint32_t WIDTH, HEIGHT;
    scene Scene;
};
