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
}
