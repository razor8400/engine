#pragma once

namespace engine
{
    struct vector2d
    {
		double m_x;
		double m_y;

		vector2d() : m_x(0), m_y(0)
		{

		}

		vector2d(double x, double y) : m_x(x), m_y(y)
		{

		}
    };
}
