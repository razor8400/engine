#pragma once

#include "../common.h"

namespace engine
{
    class window;
    
    class director
    {
    public:
        static director& instance();
        
        void set_win_size(int width, int height);
        void set_display_name(const std::string& display_name);
        void set_frame_rate(int frame_rate);
        void run();
        void stop();
        void main_loop();
        
        const vector2d& get_win_size() const { return m_win_size; }
    private:
        director();
        ~director();
        void update(float dt);
    private:
        float m_time_interval = 0;
        bool m_running = false;
        vector2d m_win_size;
        std::string m_display_name;
        
        std::unique_ptr<window> m_window;
    };
}
