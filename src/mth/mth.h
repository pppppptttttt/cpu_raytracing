#pragma once
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matr.h"
#include "ray.h"
#include "camera.h"

typedef mth::vec2<double> vec2;
using point2 = vec2;
using color2 = vec2;
typedef mth::vec3<double> vec3;
using point3 = vec3;
using color3 = vec3;
typedef mth::vec4<double> vec4;
using point4 = vec4;
using color4 = vec4;
typedef mth::matr<double> matr;
typedef mth::ray<double> ray;
typedef mth::camera<double> camera;