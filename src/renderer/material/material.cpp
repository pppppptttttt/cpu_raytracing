#include "material.h"

bool lambertian::Scatter( const ray& R, const hit_info& Info,
                          color3& Attenuation, ray& Scattered ) const
{
    vec3 scatter_dir = Info.n + mth::random_unit_vector<double>();
    if (scatter_dir.near_zero())
        scatter_dir = Info.n;
    Scattered = ray(Info.p, scatter_dir);
    Attenuation = Albedo;
    return true;
}

bool metal::Scatter( const ray& R, const hit_info& Info,
                     color3& Attenuation, ray& Scattered ) const
{
    vec3 reflected = mth::unit_vector(R.Dir - 2 * dot(R.Dir, Info.n) * Info.n);
    Scattered = ray(Info.p, reflected + Fuzz * mth::random_unit_vector<double>());
    Attenuation = Albedo;
    return (dot(Scattered.Dir, Info.n) > 0.0);
}

bool dielectric::Scatter( const ray& R, const hit_info& Info,
                          color3& Attenuation, ray& Scattered ) const
{
    Attenuation = color3(1.0);
    double ratio = Info.front_face ? (1.0 / ior) : ior;
    vec3 udir = mth::unit_vector(R.Dir);
    double co = std::clamp(dot(-udir, Info.n), -1.0, 1.0);
    double si = sqrt(1 - co * co);

    if (ratio * si > 1.0 || reflectance(co, ratio) > mth::Rnd01())
        Scattered = ray(Info.p, mth::unit_vector(R.Dir - 2 * dot(R.Dir, Info.n) * Info.n));
    else
        Scattered = ray(Info.p, refract(udir, Info.n, ratio));
    return true;
}