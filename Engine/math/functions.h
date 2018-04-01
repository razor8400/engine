#pragma once

#define M_PI       3.14159265358979323846f 

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
