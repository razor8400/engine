#pragma once

#include "math/libmath.h"

namespace engine
{
    class input_delegate
    {
    public:
        virtual bool on_mouse_down(const math::vector2d& location) = 0;
        virtual void on_mouse_move(const math::vector2d& location) = 0;
        virtual void on_mouse_up(const math::vector2d& location) = 0;
    };
}


