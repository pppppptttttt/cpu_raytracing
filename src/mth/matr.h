#pragma once
#include "mthdef.h"

namespace mth
{
    template<typename Type>
    class matr
    {
    public:
        Type M[4][4] {};

        matr( void ) :
            M {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
              }
        {}

        matr( Type a ) :
            M {
                {a, a, a, a},
                {a, a, a, a},
                {a, a, a, a},
                {a, a, a, a}
              }
        {}

        matr( Type A00, Type A01, Type A02, Type A03, 
              Type A10, Type A11, Type A12, Type A13,
              Type A20, Type A21, Type A22, Type A23,
              Type A30, Type A31, Type A32, Type A33 ) :
            M {
                {A00, A01, A02, A03},
                {A10, A11, A12, A13},
                {A20, A21, A22, A23},
                {A30, A31, A32, A33}
              }
        {}

        matr operator*( const matr& m ) const
        {
            matr r(0);
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    for (int k = 0; k < 4; k++)
                        r.M[i][j] += M[i][k] * m.M[k][j];
            return r;
        }

        matr operator*=( const matr& m )
        {
            *this = *this * m;
            return *this;
        }

        static matr Translate( const vec3<Type>& T )
        {
            return matr(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        T.x, T.y, T.z, 1);
        }

        static matr Scale( const vec3<Type>& S )
        {
            return matr(S.x, 0, 0, 0,
                        0, S.y, 0, 0,
                        0, 0, S.z, 0,
                        0, 0, 0, 1);
        }

        static matr RotateX( Type AngleInDegrees )
        {
            Type A = D2R(AngleInDegrees);
            return matr(1, 0, 0, 0,
                        0, cos(A), sin(A), 0,
                        0, -sin(A), cos(A), 0,
                        0, 0, 0, 1);
        }

        static matr RotateY( Type AngleInDegrees )
        {
            Type A = Degree2Radian(A);
            return matr(cos(A), 0, -sin(A), 0,
                        0, 1, 0, 0,
                        sin(A), 0, cos(A), 0,
                        0, 0, 0, 1);
        }

        static matr RotateZ( Type AngleInDegrees )
        {
            Type A = Degree2Radian(A);
            return matr(cos(A), sin(A), 0, 0,
                        -sin(A), cos(A), 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
        }

        static matr Rotate( const vec3<Type>& v, Type AngleInDegrees )
        {
            Type a = D2R(AngleInDegrees), si = sin(a), co = cos(a);
            vec3<Type> V = unit_vector(v);
            matr m(co + V.x * V.x * (1 - co),
                    V.x * V.y * (1 - co) + V.z * si,
                     V.x * V.z * (1 - co) - V.y * si, 
                      0,
                   V.y * V.x * (1 - co) - V.z * si,
                    co + V.y * V.y * (1 - co),
                     V.y * V.z * (1 - co) + V.x * si,
                      0,
                   V.z * V.x * (1 - co) + V.y * si,
                    V.z * V.y * (1 - co) - V.x * si,
                     co + V.z * V.z * (1 - co),
                      0,
                   0, 0, 0, 1);

            return m;
        }
    };
}