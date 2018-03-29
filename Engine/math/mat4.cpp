#include "mat4.h"

namespace engine
{
    namespace math
    {
        const mat4 mat4::identity;
        
        mat4 mat4::operator*(const mat4& m4) const
        {
            mat4 mat;
            
            mat[0] = m[0] * m4[0] + m[1] * m4[4] + m[2] * m4[8] + m[3] * m4[12];
            mat[1] = m[0] * m4[1] + m[1] * m4[5] + m[2] * m4[9] + m[3] * m4[13];
            mat[2] = m[0] * m4[2] + m[1] * m4[6] + m[2] * m4[10] + m[3] * m4[14];
            mat[3] = m[0] * m4[3] + m[1] * m4[7] + m[2] * m4[11] + m[3] * m4[15];
            
            mat[4] = m[4] * m4[0] + m[5] * m4[4] + m[6] * m4[8] + m[7] * m4[12];
            mat[5] = m[4] * m4[1] + m[5] * m4[5] + m[6] * m4[9] + m[7] * m4[13];
            mat[6] = m[4] * m4[2] + m[5] * m4[6] + m[6] * m4[10] + m[7] * m4[14];
            mat[7] = m[4] * m4[3] + m[5] * m4[7] + m[6] * m4[11] + m[7] * m4[15];
            
            mat[8] = m[8] * m4[0] + m[9] * m4[4] + m[10] * m4[8] + m[11] * m4[12];
            mat[9] = m[8] * m4[1] + m[9] * m4[5] + m[10] * m4[9] + m[11] * m4[13];
            mat[10] = m[8] * m4[2] + m[9] * m4[6] + m[10] * m4[10] + m[11] * m4[14];
            mat[11] = m[8] * m4[3] + m[9] * m4[7] + m[10] * m4[11] + m[11] * m4[15];
            
            mat[12] = m[12] * m4[0] + m[13] * m4[4] + m[14] * m4[8] + m[15] * m4[12];
            mat[13] = m[12] * m4[1] + m[13] * m4[5] + m[14] * m4[9] + m[15] * m4[13];
            mat[14] = m[12] * m4[2] + m[13] * m4[6] + m[14] * m4[10] + m[15] * m4[14];
            mat[15] = m[12] * m4[3] + m[13] * m4[7] + m[14] * m4[11] + m[15] * m4[15];
            
            return mat;
        }
    }
}
