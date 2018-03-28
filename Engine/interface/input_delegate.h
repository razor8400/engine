#pragma once

#include "common.h"

namespace engine
{
    class input_delegate
    {
    public:
        virtual bool on_mouse_down(const vector2d& location) = 0;
        virtual void on_mouse_move(const vector2d& location) = 0;
        virtual void on_mouse_up(const vector2d& location) = 0;
    };
}


