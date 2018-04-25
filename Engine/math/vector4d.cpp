#include "vector4d.h"

namespace math
{
    const vector4d vector4d::zero = vector4d();
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
    
    vector4d operator*(const mat4& m4, const vector4d& v4)
    {
        vector4d result;
        
        result.x = m4[0] * v4.x + m4[1] * v4.y + m4[2] * v4.z + m4[3] * v4.w;
        result.y = m4[4] * v4.x + m4[5] * v4.y + m4[6] * v4.z + m4[7] * v4.w;
        result.z = m4[8] * v4.x + m4[9] * v4.y + m4[10] * v4.z + m4[11] * v4.w;
        result.w = m4[12] * v4.x + m4[13] * v4.y + m4[14] * v4.z + m4[15] * v4.w;
        
        return result;
    }

    vector4d vector4d::operator*(const mat4& m4) const
    {
        vector4d result;
        
        result.x = m4[0] * x + m4[1] * y + m4[2] * z + m4[3] * w;
        result.y = m4[4] * x + m4[5] * y + m4[6] * z + m4[7] * w;
        result.z = m4[8] * x + m4[9] * y + m4[10] * z + m4[11] * w;
        result.w = m4[12] * x + m4[13] * y + m4[14] * z + m4[15] * w;
        
        return result;
    }
}

