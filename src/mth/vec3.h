#pragma once
#include "mthdef.h"

namespace mth
{
    template<typename Type>
    class vec3
    {
    public:
        Type x, y, z;

        vec3( void ) : x(0), y(0), z(0)
        {}

        vec3( Type X, Type Y, Type Z ) : x(X), y(Y), z(Z)
        {}

        vec3( Type A ) : x(A), y(A), z(A)
        {}

        inline operator Type*() { return &x; }
        inline Type operator[]( uint32_t i ) const
        {
            assert(i <= 2);
            return *(&x + i);
        }
        inline Type& operator[]( uint32_t i )
        {
            assert(i <= 2);
            return *(&x + i);
        }
        inline vec3 operator-( void ) const { return vec3(-x, -y, -z); }
        inline vec3 operator+( const vec3& v ) const { return vec3(x + v.x, y + v.y, z + v.z); }
        inline vec3 operator-( const vec3& v ) const { return vec3(x - v.x, y - v.y, z - v.z); }
        inline vec3 operator/( Type a ) const { return vec3(x / a, y / a, z / a); }
        inline vec3 operator*( const vec3& v ) const { return vec3(x * v.x, y * v.y, z * v.z); }
        inline vec3 operator*( Type a ) const { return vec3(x * a, y * a, z * a); }
        inline vec3& operator+=( const vec3& v )
        {
            x += v.x, y += v.y, z += v.z;
            return *this;
        }
        inline vec3& operator-=( const vec3& v )
        {
            return (*this += -v);
        }
        inline vec3& operator*=( Type N )
        {
            x *= N, y *= N, z *= N;
            return *this;
        }
        inline vec3& operator*=( const vec3& v )
        {
            *this = *this * v;
            return *this;
        }
        inline vec3& operator/=( Type N )
        {
            x /= N, y /= N, z /= N;
            return *this;
        }
        inline Type length2( void ) const
        {
            return dot(*this, *this);
        }
        inline Type length( void ) const
        {
            return sqrt(length2());
        }
        static inline vec3<Type> Rnd01()
        {
            return vec3<Type>(mth::Rnd01(), mth::Rnd01(), mth::Rnd01());
        }
        inline bool near_zero() const
        {
            return (fabs(x) < THR) && (fabs(y) < THR) && (fabs(z) < THR);
        }
    };

    template<typename Type>
    inline std::ostream& operator<<( std::ostream& out, const vec3<Type>& v )
    {
        return out << v.x << ' ' << v.y << ' ' << v.z;
    }

    template<typename Type>
    inline vec3<Type> operator*( Type a, const vec3<Type>& v )
    {
        return v * a;
    }

    template<typename Type>
    inline Type dot( const vec3<Type>& a, const vec3<Type>& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template<typename Type>
    inline vec3<Type> cross( const vec3<Type>& a, const vec3<Type>& b )
    {
        return vec3<Type>(a.y * b.z - a.z * b.y,
                          a.z * b.x - a.x * b.z,
                          a.x * b.y - a.y * b.x);
    }

    template<typename Type>
    inline vec3<Type> unit_vector( const vec3<Type>& v )
    {
        return v / v.length();
    }

    template<typename Type>
    inline vec3<Type> random_in_unit_sphere()
    {
        vec3<Type> p;
        do
        {
            p = vec3<Type>::Rnd01();
        } while (p.length2() > 1);
        return p;
    }

    template<typename Type>
    inline vec3<Type> random_unit_vector()
    {
        return unit_vector<Type>(random_in_unit_sphere<Type>());
    }

    template<typename Type>
    inline vec3<Type> random_on_hemisphere( const vec3<Type>& n )
    {
        vec3<Type> p = random_unit_vector<Type>();
        if (dot(p, n) > 0)
            return p;
        return -p;
    }

    template<typename Type>
    inline vec3<Type> sqrt( const vec3<Type>& v )
    {
        return vec3<Type>(std::sqrt(v[0]), std::sqrt(v[1]), std::sqrt(v[2]));
    }
}