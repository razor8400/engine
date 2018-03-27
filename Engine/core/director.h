#pragma once

#include "common.h"

namespace engine
{   
    class director
    {
    public:
        static director& instance();
        
		void set_frame_rate(int frame_rate);
        void start();
        void stop();
        void main_loop();
    private:
        director();
        ~director();
        void update(float dt);
    private:
        float m_time_interval = 0;
        bool m_running = false;
    };
}
