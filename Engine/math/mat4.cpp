#include <math.h>
#include <cmath>

#include "mat4.h"
#include "functions.h"

namespace engine
{
    namespace math
    {
        const mat4 mat4::identity;
        
        mat4 mat4::operator*(const mat4& m4) const
        {
            mat4 mat;
            
            mat[0] = m[0] * m4[0] + m[4] * m4[1] + m[8] * m4[2] + m[12] * m4[3];
            mat[1] = m[1] * m4[0] + m[5] * m4[1] + m[9] * m4[2] + m[13] * m4[3];
            mat[2] = m[2] * m4[0] + m[6] * m4[1] + m[10] * m4[2] + m[14] * m4[3];
            mat[3] = m[3] * m4[0] + m[7] * m4[1] + m[11] * m4[2] + m[15] * m4[3];
            
            mat[4] = m[0] * m4[4] + m[4] * m4[5] + m[8] * m4[6] + m[12] * m4[7];
            mat[5] = m[1] * m4[4] + m[5] * m4[5] + m[9] * m4[6] + m[13] * m4[7];
            mat[6] = m[2] * m4[4] + m[6] * m4[5] + m[10] * m4[6] + m[14] * m4[7];
            mat[7] = m[3] * m4[4] + m[7] * m4[5] + m[11] * m4[6] + m[15] * m4[7];
            
            mat[8] = m[0] * m4[8] + m[4] * m4[9] + m[8] * m4[10] + m[12] * m4[11];
            mat[9] = m[1] * m4[8] + m[5] * m4[9] + m[9] * m4[10] + m[13] * m4[11];
            mat[10] = m[2] * m4[8] + m[6] * m4[9] + m[10] * m4[10] + m[14] * m4[11];
            mat[11] = m[3] * m4[8] + m[7] * m4[9] + m[11] * m4[10] + m[15] * m4[11];
            
            mat[12] = m[0] * m4[12] + m[4] * m4[13] + m[8] * m4[14] + m[12] * m4[15];
            mat[13] = m[1] * m4[12] + m[5] * m4[13] + m[9] * m4[14] + m[13] * m4[15];
            mat[14] = m[2] * m4[12] + m[6] * m4[13] + m[10] * m4[14] + m[14] * m4[15];
            mat[15] = m[3] * m4[12] + m[7] * m4[13] + m[11] * m4[14] + m[15] * m4[15];
            
            return mat;
        }

		mat4 mat4::operator*(float f) const
		{
			mat4 mat;

			for (int i = 0; i < 4 * 4; ++i)
				mat[i] = m[i] * f;

			return mat;
		}

		mat4 mat4::translate(float x, float y, float z)
		{
			mat4 mat;

			mat[3] = x;
			mat[7] = y;
			mat[11] = z;

			return mat;
		}

		mat4 mat4::rotate(float x, float y, float z)
		{
			mat4 mat;

			return mat;
		}

		mat4 mat4::scale(float x, float y, float z)
		{
			mat4 mat;

			mat[0] = x;
			mat[5] = y;
			mat[10] = z;
			
			return mat;
		}

		mat4 mat4::look_at(const vector3d& eye, const vector3d& target, const vector3d& up)
		{
			mat4 mat;

			auto normalized_eye = vector3d::normalize(eye);

			auto zaxis = vector3d::normalize(target - eye);
			auto xaxis = vector3d::normalize(vector3d::cross(up, zaxis));
			auto yaxis = vector3d::normalize(vector3d::cross(zaxis, xaxis));
			
			mat[0] = xaxis.x;
			mat[1] = xaxis.y;
			mat[2] = xaxis.z;
			mat[3] = -vector3d::dot(xaxis, normalized_eye);
			
			mat[4] = yaxis.x;
			mat[5] = yaxis.y;
			mat[6] = yaxis.z;
			mat[7] = -vector3d::dot(yaxis, normalized_eye);

			mat[8] = zaxis.x;			
			mat[9] = zaxis.y;
			mat[10] = zaxis.z;
			mat[11] = -vector3d::dot(zaxis, normalized_eye);

			return mat;
		}

		mat4 mat4::perspective(float fow, float aspect_ratio, float near_plane, float far_plane)
		{
			mat4 mat;

			float tangent = tan(deg_to_rad(fow) * 0.5f);

			mat[0] = 1.0f / (aspect_ratio * tangent);
			mat[5] = 1.0f / tangent;

            mat[10] = (far_plane + near_plane) / (far_plane - near_plane);
			mat[11] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);

			mat[14] = 1.0f;

			return mat;
		}
        
        mat4 mat4::ortographic(float width, float height, float near_plane, float far_plane)
        {
            mat4 mat;
            
            float half_width = width / 2.0f;
            float half_height = height / 2.0f;
            
            float left = -half_width;
            float right = half_width;
            float bottom = -half_height;
            float top = half_height;
            
            mat[0] = 2 / (right - left);
            mat[5] = 2 / (top - bottom);
            mat[10] = 2 / (near_plane - far_plane);
            
            mat[3] = (left + right) / (left - right);
            mat[7] = (top + bottom) / (bottom - top);
            mat[11] = (near_plane + far_plane) / (near_plane - far_plane);
            
            return mat;
        }
	}
}
