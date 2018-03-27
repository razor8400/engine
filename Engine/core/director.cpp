#include <chrono>

#include "debug.h"
#include "director.h"
#include "../platform/window.h"

namespace engine
{
    director& director::instance()
    {
        static director instance;
        return instance;
    }
    
    director::director()
    {
        
    }
    
    director::~director()
    {

    }
    
    void director::set_win_size(int width, int height)
    {
        m_win_size.x = width;
        m_win_size.y = height;
    }
    
    void director::set_display_name(const std::string& display_name)
    {
        m_display_name = display_name;
    }
    
    void director::set_frame_rate(int frame_rate)
    {
        m_time_interval = 1.0f / frame_rate;
    }
    
    void director::run()
    {
        m_running = true;
        m_window = std::make_unique<window>(m_display_name.c_str(), m_win_size.x, m_win_size.y);
        m_window->begin_render();
    }
    
    void director::stop()
    {
        m_running = false;
    }
    
    void director::main_loop()
    {
        if (m_running)
        {
            static auto last_update = std::chrono::high_resolution_clock::now();
            
            auto now = std::chrono::high_resolution_clock::now();
            auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_update);
            auto count = delta.count();
            
            if (count >= m_time_interval)
            {
                last_update = now;
                update(count);
            }
        }
    }
    
    void director::update(float dt)
    {
        LOG("%f", dt);
    }
}
