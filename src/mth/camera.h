#pragma once
#include "vec3.h"

namespace mth
{
    template<typename Type>
    class camera
    {
    public:
        camera( uint32_t W, uint32_t H, Type vFov = 90.0 ) :
            Ws(W), Hs(H), Loc({0}), At({0, 0, -1}), vfov(vFov)
        {
            Set(Loc, At, vfov);
        }

        camera& Set( const vec3<Type>& NewLoc, const vec3<Type>& NewAt, double vFov )
        {
            Loc = NewLoc, At = NewAt, vfov = vFov;
            // calc projection width and height according to fov
            FocalLength = (Loc - At).length();
            Type theta = vfov / 180.0 * PI;
            Type h = tan(theta/2);
            Hp = Wp = ProjSize * h * FocalLength;
            if (Ws > Hs)
                Wp *= static_cast<Type>(Ws) / Hs;
            else
                Hp *= static_cast<Type>(Hs) / Ws;

            // calc camera base
            w = unit_vector(Loc - At);
            u = unit_vector(cross(Up, w));
            v = cross(w, u);

            // calculate viewport base vectors
            ViewportU = Wp * u;
            ViewportDU = ViewportU / Ws;
            ViewportV = -Hp * v;
            ViewportDV = ViewportV / Hs;
            ViewportUpperLeft = Loc - w * FocalLength - ViewportU / 2 - ViewportV / 2;
            ViewportOrigin = ViewportUpperLeft + 0.5 * (ViewportDU + ViewportDV);

            return *this;
        }

        ray<Type> GetThresholdedRay( uint32_t x, uint32_t y ) const
        {
            auto pixel_dev_square = ViewportDU * (-0.5 + Rnd01()) + ViewportDV * (-0.5 + Rnd01());
            auto pixel_center = ViewportOrigin + (static_cast<double>(x) * ViewportDU) + (static_cast<double>(y) * ViewportDV);
            return ray<Type>(Loc, pixel_center + pixel_dev_square - Loc);
        }
    private:
        uint32_t Ws, Hs;
        Type Wp, Hp, FocalLength;
        const Type ProjSize = 2;

        vec3<Type>
            Loc, At;
        Type vfov;
        const vec3<Type> Up {0, 1, 0};

        vec3<Type>
            u, v, w,    // camera coordinate system base vectors
            ViewportU,
            ViewportV,
            ViewportDU,
            ViewportDV,
            ViewportUpperLeft,
            ViewportOrigin;
    };
}