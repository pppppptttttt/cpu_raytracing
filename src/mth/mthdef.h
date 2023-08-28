#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <random>

#define PI 3.14159265358979323846f
#define D2R(X) ((X) * PI / 180)
#define R2D(X) ((X) * 180 / PI)
#define THR 1e-9

namespace mth
{
    template<typename Type> class vec2;
    template<typename Type> class vec3;
    template<typename Type> class vec4;
    template<typename Type> class matr;
    template<typename Type> class camera;

    inline double Rnd01()
    {
        static thread_local std::mt19937 generator;
        std::uniform_int_distribution<int> distribution(0, INT32_MAX);
        return static_cast<double>(distribution(generator)) / INT32_MAX;
    }
}