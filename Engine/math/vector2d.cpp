#include "vector2d.h"

namespace engine
{
    namespace math
    {
        const vector2d vector2d::zero;
        
        vector2d::vector2d() : x(0), y(0)
        {
            
        }
        
        vector2d::vector2d(double x1, double y1) : x(x1), y(y1)
        {
            
        }
    }
}

