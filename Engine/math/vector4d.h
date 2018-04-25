#pragma once

#include "mat4.h"
#include "vector3d.h"

namespace math
{
    struct vector4d
    {
        float x, y, z, w;
    
        vector4d();
        vector4d(float x1, float y1, float z1, float w1);
        vector4d(const vector3d& v3);
        
        friend vector4d operator*(const mat4& m4, const vector4d& v4);
        vector4d operator*(const mat4& m4) const;
        
        static const vector4d one;
        static const vector4d zero;
    };
}
