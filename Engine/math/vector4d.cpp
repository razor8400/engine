#include "vector4d.h"

namespace engine
{
    namespace math
    {
        vector4d vector4d::operator*(const mat4& mat) const
        {
            vector4d v4;
            
            v4.x = mat.m[0] * v4.x + mat.m[1] * v4.y + mat.m[2] * v4.z + mat.m[3] * v4.w;
            v4.y = mat.m[4] * v4.x + mat.m[5] * v4.y + mat.m[6] * v4.z + mat.m[7] * v4.w;
            v4.z = mat.m[8] * v4.x + mat.m[9] * v4.y + mat.m[10] * v4.z + mat.m[11] * v4.w;
            v4.w = mat.m[12] * v4.x + mat.m[13] * v4.y + mat.m[14] * v4.z + mat.m[15] * v4.w;
            
            return v4;
        }
    }
}
