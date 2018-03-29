#pragma once

namespace engine
{
    namespace math
    {
        class mat4
        {
            float m[16] = {
                1, 0, 0, 0, // 0,  1,  2,  3
                0, 1, 0, 0, // 4,  5,  6,  7
                0, 0, 1, 0, // 8,  9,  10, 11
                0, 0, 0, 1  // 12, 13, 14, 15
            };
            
            float& operator[](int a)
            {
                return m[a];
            }
            
            float& operator[](int a) const
            {
                return m[a];
            }
            
            static const mat4 identity;
            
            mat4 operator*(const mat4& m4) const;
        };
    }
}
