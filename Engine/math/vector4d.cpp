#include "vector4d.h"

namespace math
{
    const vector4d vector4d::one = vector4d(1, 1, 1, 1);
    
    vector4d::vector4d() : x(0), y(0), z(0), w(0)
    {

    }

    vector4d::vector4d(float x1, float y1, float z1, float w1) : x(x1), y(y1), z(z1), w(w1)
    {

    }
    
    vector4d::vector4d(const vector3d& v3) : x(v3.x), y(v3.y), z(v3.z)
    {
        
    }

    vector4d vector4d::operator*(const mat4& mat) const
    {
        vector4d v4;
        
        v4.x = mat[0] * x + mat[1] * y + mat[2] * z + mat[3] * w;
        v4.y = mat[4] * x + mat[5] * y + mat[6] * z + mat[7] * w;
        v4.z = mat[8] * x + mat[9] * y + mat[10] * z + mat[11] * w;
        v4.w = mat[12] * x + mat[13] * y + mat[14] * z + mat[15] * w;
        
        return v4;
    }
}

