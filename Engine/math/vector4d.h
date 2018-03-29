#pragma once

#include "mat4.h"

namespace engine
{
    namespace math
    {
        struct vector4d
        {
            double x, y, z, w;
        
			vector4d();
			vector4d(double x1, double y1, double z1, double w1);
            vector4d operator*(const mat4& m4) const;
        };
    }
}
