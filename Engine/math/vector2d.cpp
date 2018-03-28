#include "vector2d.h"

namespace engine
{
    vector2d vector2d::zero;
    
    vector2d::vector2d() : m_x(0), m_y(0)
    {
        
    }
    
    vector2d::vector2d(double x, double y) : m_x(x), m_y(y)
    {
        
    }
}

