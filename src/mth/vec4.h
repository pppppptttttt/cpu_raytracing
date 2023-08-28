#pragma once
#include "mthdef.h"

namespace mth
{
    template<typename Type>
    class vec4
    {
    public:
        Type x, y, z, w;

        vec4( void ) : x(0), y(0), z(0), w(0)
        {}

        vec4( Type X, Type Y, Type Z, Type W ) : x(X), y(Y), z(Z), w(W)
        {}

        vec4( Type A ) : x(A), y(A), z(A), w(A)
        {}

        inline operator Type*() { return &x; }
        inline Type operator[]( uint32_t i ) const
        {
            assert(i <= 3);
            return *(&x + i);
        }
        inline Type& operator[]( uint32_t i )
        {
            assert(i <= 3);
            return *(&x + i);
        }
        inline vec4 operator-( void ) const { return vec4(-x, -y, -z, -w); }
        inline vec4 operator+( const vec4& v ) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
        inline vec4 operator-( const vec4& v ) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
        inline vec4 operator/( Type a ) const { return vec4(x / a, y / a, z / a, w/a); }
        inline vec4 operator*( const vec4& v ) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
        inline vec4 operator*( Type a ) const { return vec4(x * a, y * a, z * a, w * a); }
        inline vec4& operator+=( const vec4& v )
        {
            x += v.x, y += v.y, z += v.z, w += v.w;
            return *this;
        }
        inline vec4& operator-=( const vec4& v )
        {
            return (*this += -v);
        }
        inline vec4& operator*=( Type N )
        {
            x *= N, y *= N, z *= N, w *= N;
            return *this;
        }
        inline vec4& operator*=( const vec4& v )
        {
            *this = *this * v;
            return *this;
        }
        inline vec4& operator/=( Type N )
        {
            x /= N, y /= N, z /= N, w /= N;
            return *this;
        }
   };

    template<typename Type>
    inline std::ostream& operator<<( std::ostream& out, const vec4<Type>& v )
    {
        return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
    }

    template<typename Type>
    inline vec4<Type> operator*( Type a, const vec4<Type>& v )
    {
        return v * a;
    }
}
