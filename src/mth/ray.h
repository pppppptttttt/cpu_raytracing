#pragma once
#include "vec3.h"

namespace mth
{
    template<typename type>
    class ray
    {
    public:
        vec3<type> Origin;
        vec3<type> Dir;

        ray() {}
        ray( const vec3<type>& orig, const vec3<type>& dir ) : Origin(orig), Dir(unit_vector(dir)) {}

        inline vec3<type> at( type t ) const
        {
            return vec3<type>(Origin + Dir * t);
        }
    };
}