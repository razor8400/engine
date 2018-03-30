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

		mat4 mat4::operator*(float f) const
		{
			mat4 mat;

			mat[0] = m[0] * f;
			mat[1] = m[1] * f;
			mat[2] = m[2] * f;
			mat[3] = m[3] * f;

			mat[4] = m[4] * f;
			mat[5] = m[5] * f;
			mat[6] = m[6] * f;
			mat[7] = m[7] * f;

			mat[8] = m[8] * f;
			mat[9] = m[9] * f;
			mat[10] = m[10] * f;
			mat[11] = m[11] * f;

			mat[12] = m[12] * f;
			mat[13] = m[13] * f;
			mat[14] = m[14] * f;
			mat[15] = m[15] * f;

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
			mat[1] = yaxis.x;
			mat[2] = zaxis.x;

			mat[4] = xaxis.y;
			mat[5] = yaxis.y;
			mat[6] = zaxis.y;

			mat[8] = xaxis.z;
			mat[9] = yaxis.z;
			mat[10] = yaxis.z;

			mat[12] = -vector3d::dot(xaxis, normalized_eye);
			mat[13] = -vector3d::dot(yaxis, normalized_eye);
			mat[14] = -vector3d::dot(zaxis, normalized_eye);

			return mat;
		}

		mat4 mat4::perspective(float fow, float aspect_ratio, float near_plane, float far_plane)
		{
			mat4 mat;

			float tangent = tan(deg_to_rad(fow) * 0.5f);

			mat[0] = 1.0f / (aspect_ratio * tangent);
			mat[5] = 1.0f / tangent;

            mat[10] = (far_plane + near_plane) / (far_plane - near_plane);
			mat[11] = 1.0f;
			mat[14] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);

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
            
            mat[12] = (left + right) / (left - right);
            mat[13] = (top + bottom) / (bottom - top);
            mat[14] = (near_plane + far_plane) / (near_plane - far_plane);
            
            return mat;
        }
	}
}
