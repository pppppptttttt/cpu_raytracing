#pragma once
#include "../material/material.h"
#include <memory>

class scene;
class material;
struct hit_info
{
    vec3 n;
    point3 p;
    double t;
    bool front_face;
    material* mtl;

    inline void set_face_normal( const ray& R, const vec3& N )
    {
        front_face = dot(R.Dir, N) < 0.0;
        n = front_face ? N : -N;
    }
};

class shape
{
public:
    virtual bool Hits( const ray& R, hit_info& Info ) const = 0;
    virtual ~shape() = default;
};

class sphere : public shape
{
public:
    sphere( const point3& c, double r, material* mtl ) : C(c), Radius(r), Mtl(mtl) {}
    bool Hits( const ray& R, hit_info& Info ) const override;
private:
    point3 C;
    double Radius;
    material* Mtl;
};

class triangle : public shape
{
public:
    triangle( const point3& p0, const point3& p1, const point3& p2, material* mtl ) : p0(p0), p1(p1), p2(p2), Mtl(mtl) {}
    bool Hits( const ray& R, hit_info& Info ) const override;
private:
    point3 p0, p1, p2;
    material* Mtl;
};

class model : public shape
{
public:
    model( const std::string& fn, material* mtl );
    bool Hits( const ray& R, hit_info& Info ) const override;
private:
    std::vector<std::shared_ptr<triangle>> Triangles;
    material* Mtl;
};