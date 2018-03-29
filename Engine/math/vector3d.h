#pragma once

namespace engine
{
    namespace math
    {
        struct vector3d
        {
            double x, y, z;
            
            vector3d();
            vector3d(double x1, double y1, double z1);
            
            static const vector3d zero;
            static const vector3d up;
            static const vector3d left;
            static const vector3d down;
            static const vector3d right;
        };
    }
}
