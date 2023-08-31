#pragma once
#include <algorithm>
#include "../../def.h"
#include "../shapes/shapes.h"

struct hit_info;
class material
{
public:
    virtual ~material() = default;
    virtual bool Scatter( const ray& R, const hit_info& Info,
                          color3& Attenuation, ray& Scattered ) const = 0;
};

class lambertian : public material
{
public:
    lambertian( const color3& a ) : Albedo(a) {}

    bool Scatter( const ray& R, const hit_info& Info,
                  color3& Attenuation, ray& Scattered ) const override;
private:
    color3 Albedo;
};

class metal : public material
{
public:
    metal( const color3& a, double f ) : Albedo(a), Fuzz(std::clamp(f, -1.0, 1.0)) {}

    bool Scatter( const ray& R, const hit_info& Info,
                  color3& Attenuation, ray& Scattered ) const override;
private:
    color3 Albedo;
    double Fuzz;
};