#pragma once

#include "ref.h"

namespace engine
{
    typedef std::function<void()> touch_callback;
    
    class touch_listener : public ref
    {
    public:
        touch_callback on_touch_began;
        touch_callback on_touch_move;
        touch_callback on_touch_ended;
    };
}
