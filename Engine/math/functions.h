#pragma once

#include <math.h>

namespace engine
{
    namespace math
    {
        static float deg_to_rad(float rotation)
        {
            return rotation * M_PI / 180;
        }
    }
}
