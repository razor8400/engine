#pragma once

#ifndef M_PI
#define M_PI       3.14159265358979323846f
#endif

namespace math
{
    static float deg_to_rad(float rotation)
    {
        return rotation * M_PI / 180;
    }
    
    static float line_equation(const math::vector2d& a, const math::vector2d& b, const math::vector2d& d)
    {
        return (d.x - a.x) * (b.y - a.y) - (d.y - a.y) * (b.x - a.x);
    }
}
