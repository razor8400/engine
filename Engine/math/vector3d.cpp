#include <math.h>
#include "vector3d.h"

namespace engine
{
    namespace math
    {
		const vector3d vector3d::zero;
		const vector3d vector3d::up = vector3d(0, 1, 0);

		const vector3d vector3d::left = vector3d(-1, 0, 0);
		const vector3d vector3d::down = vector3d(0, -1, 0);
		const vector3d vector3d::right = vector3d(1, 0, 0);

        vector3d::vector3d() : x(0), y(0), z(0)
        {
            
        }
        
        vector3d::vector3d(double x1, double y1, double z1) : x(x1), y(y1), z(z1)
        {
            
        }

		vector3d vector3d::operator+(const vector3d& v3) const
		{
			return vector3d(x + v3.x, y + v3.y, z + v3.z);
		}

		vector3d vector3d::operator-(const vector3d& v3) const
		{
			return vector3d(x - v3.x, y - v3.y, z - v3.z);
		}

		float vector3d::lenght() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float vector3d::dot(const vector3d& v1, const vector3d& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		vector3d vector3d::normalize(const vector3d& v3)
		{
			auto lenght = v3.lenght();

			vector3d r;
			
			r.x = v3.x / lenght;
			r.y = v3.y / lenght;
			r.z = v3.z / lenght;

			return r;
		}

		vector3d vector3d::cross(const vector3d& v1, const vector3d& v2)
		{
			vector3d r;

			r.x = v1.y * v2.z - v1.z * v2.y;
			r.y = v1.x * v2.z - v1.z * v2.x;
			r.z = v1.x * v2.y - v1.y * v2.x;
			return r;
		}
	}
}
