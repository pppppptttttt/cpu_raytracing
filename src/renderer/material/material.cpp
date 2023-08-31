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
    //return true;
    return (dot(Scattered.Dir, Info.n) > 0.0);
}