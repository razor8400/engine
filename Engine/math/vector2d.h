#pragma once

namespace engine
{
    namespace math
    {
        struct vector2d
        {
            double x;
            double y;
            
            vector2d();
            vector2d(double x, double y);
            
            static const vector2d zero;
        };
    }
}
