#pragma once

#include "core/ref.h"

namespace engine
{
    class touch_listener : public ref
    {
    public:
		DECLARE_CLASS;

        ~touch_listener();
        
        bool on_touch_began();
        void on_touch_moved();
        void on_touch_ended();
    public:
        std::function<bool()> touch_began;
        std::function<void()> touch_moved;
        std::function<void()> touch_ended;
    };
}
