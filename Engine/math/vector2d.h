#pragma once

namespace engine
{
    struct vector2d
    {
		double m_x;
		double m_y;

        vector2d();
        vector2d(double x, double y);

        static vector2d zero;
    };
}
