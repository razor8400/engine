#include "vector4d.h"

namespace engine
{
    namespace math
    {
		vector4d::vector4d() : x(0), y(0), z(0), w(0)
		{

		}

		vector4d::vector4d(double x1, double y1, double z1, double w1) : x(x1), y(y1), z(z1), w(w1)
		{

		}

        vector4d vector4d::operator*(const mat4& mat) const
        {
            vector4d v4;
            
            v4.x = mat[0] * v4.x + mat[1] * v4.y + mat[2] * v4.z + mat[3] * v4.w;
            v4.y = mat[4] * v4.x + mat[5] * v4.y + mat[6] * v4.z + mat[7] * v4.w;
            v4.z = mat[8] * v4.x + mat[9] * v4.y + mat[10] * v4.z + mat[11] * v4.w;
            v4.w = mat[12] * v4.x + mat[13] * v4.y + mat[14] * v4.z + mat[15] * v4.w;
            
            return v4;
        }
    }
}
