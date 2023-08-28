#pragma once
#include "mthdef.h"

namespace mth
{
    template<typename Type>
    class vec2
    {
    public:
        Type x, y;

        vec2( void ) : x(0), y(0)
        {}

        vec2( Type X, Type Y ) : x(X), y(Y)
        {}

        vec2( Type A ) : x(A), y(A)
        {}

        inline operator Type*() { return &x; }
        inline Type operator[]( uint32_t i ) const
        {
            assert(i <= 1);
            return *(&x + i);
        }
        inline Type& operator[]( uint32_t i )
        {
            assert(i <= 1);
            return *(&x + i);
        }
        inline vec2 operator-( void ) const { return vec2(-x, -y); }
        inline vec2 operator+( const vec2& v ) const { return vec2(x + v.x, y + v.y); }
        inline vec2 operator-( const vec2& v ) const { return vec2(x - v.x, y - v.y); }
        inline vec2 operator/( Type a ) const { return vec2(x / a, y / a); }
        inline vec2 operator*( const vec2& v ) const { return vec2(x * v.x, y * v.y); }
        inline vec2 operator*( Type a ) const { return vec2(x * a, y * a); }
        inline vec2& operator+=( const vec2& v )
        {
            x += v.x, y += v.y;
            return *this;
        }
        inline vec2& operator-=( const vec2& v )
        {
            return (*this += -v);
        }
        inline vec2& operator*=( Type N )
        {
            x *= N, y *= N;
            return *this;
        }
        inline vec2& operator*=( const vec2& v )
        {
            *this = *this * v;
            return *this;
        }
        inline vec2& operator/=( Type N )
        {
            x /= N, y /= N;
            return *this;
        }
        inline Type length2( void )
        {
            return dot(*this, *this);
        }
        inline Type length( void )
        {
            if constexpr (std::is_same_v<Type, float>)
                return sqrtf(length2());
            else
                return sqrt(length2());
        }
    };

    template<typename Type>
    inline std::ostream& operator<<( std::ostream& out, const vec2<Type>& v )
    {
        return out << v.x << ' ' << v.y;
    }

    template<typename Type>
    inline vec2<Type> operator*( Type a, const vec2<Type>& v )
    {
        return v * a;
    }

    template<typename Type>
    inline Type dot( const vec2<Type>& a, const vec2<Type>& b )
    {
        return a.x * b.x + a.y * b.y;
    }

    template<typename Type>
    inline Type cross( const vec2<Type>& a, const vec2<Type>& b )
    {
        return a.x * b.y - a.y * b.x;
    }

    template<typename Type>
    inline vec2<Type> unit_vector( const vec2<Type>& v )
    {
        return v / v.length();
    }
}