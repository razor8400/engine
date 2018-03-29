#pragma once

#include "vector3d.h"

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
            
		public:
            float& operator[](int a) { return m[a]; }
            const float& operator[](int a) const { return m[a]; }
                        
            mat4 operator*(const mat4& m4) const;
			mat4 operator*(float f) const;

			static mat4 translate(float x, float y, float z);
			static mat4 rotate(float x, float y, float z);
			static mat4 scale(float x, float y, float z);

			static mat4 look_at(const vector3d& eye, const vector3d& target, const vector3d& up = vector3d::up);
			static mat4 perspective(float fow, float aspect_ratio, float near_plane, float far_plane);
        
			static const mat4 identity;
		};
    }
}
