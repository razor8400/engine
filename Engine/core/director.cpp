#include <chrono>

#include "core/director.h"
#include "platform/window.h"

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
        
    void director::set_frame_rate(int frame_rate)
    {
        m_time_interval = 1.0f / frame_rate;
    }
    
    void director::start()
    {
        m_running = true;
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
            auto delta = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_update);
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
		printf("%f \n", dt);
    }
}
