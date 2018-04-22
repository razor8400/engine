#pragma once

namespace engine
{
    class touch_listener;
    
    class touch_dispatcher
    {
    public:
        static touch_dispatcher& instance();
    private:
        touch_dispatcher();
        ~touch_dispatcher();
    private:
        vector<touch_listener> listeners;
    };
}
