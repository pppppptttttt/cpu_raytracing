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
            auto pixel_center = ViewportOrigin + (static_cast<Type>(x) * ViewportDU) + (static_cast<Type>(y) * ViewportDV);
            return ray<Type>(Loc, pixel_center + pixel_dev_square - Loc);
        }

        ray<Type> GetSampledRay( uint32_t x, uint32_t y, uint32_t sample_no ) const
        {
            auto pixel_center = ViewportOrigin + static_cast<Type>(x) * ViewportDU + static_cast<Type>(y) * ViewportDV;
            auto pixel_dev = ViewportDU * jitter_matrix[sample_no].x + ViewportDV * jitter_matrix[sample_no].y;
            return ray<Type>(Loc, pixel_center + pixel_dev - Loc);
        }

        ray<Type> GetRay( uint32_t x, uint32_t y ) const
        {
            auto pixel_center = ViewportOrigin + static_cast<Type>(x) * ViewportDU + static_cast<Type>(y) * ViewportDV;
            return ray<Type>(Loc, pixel_center - Loc);
        }

        camera& SetupSamplesMatrix( uint32_t SamplesPerPixel )
        {
            Type side = ceil(std::sqrt(SamplesPerPixel));
            jitter_matrix.resize(side * side);
            for (uint32_t y = 0; y < side; y++)
                for (uint32_t x = 0; x < side; x++)
                    jitter_matrix[y * side + x] =
                    {
                        x / side - 0.5 + 1 / static_cast<Type>(SamplesPerPixel),
                        y / side - 0.5 + 1 / static_cast<Type>(SamplesPerPixel)
                    };
            return *this;
        }

private:
        std::vector<vec2<Type>> jitter_matrix;

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