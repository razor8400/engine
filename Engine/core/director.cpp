#include <chrono>

#include "core/director.h"
#include "core/scene.h"

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
    
    void director::start(scene* scene)
    {
        m_running = true;
		m_scene = scene;
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

				if (m_scene)
					m_scene->draw();
            }
        }
    }
    
	void director::handle_mouse_down(const vector2d& location)
	{
		if (m_scene)
			m_scene->on_mouse_down(location);
	}

	void director::handle_mouse_move(const vector2d& location)
	{
		if (m_scene)
			m_scene->on_mouse_move(location);
	}

	void director::handle_mouse_up(const vector2d& location)
	{
		if (m_scene)
			m_scene->on_mouse_up(location);
	}

	void director::update(float dt)
    {
		if (m_scene)
			m_scene->update(dt);
    }
}
