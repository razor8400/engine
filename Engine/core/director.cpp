#include <chrono>

#include "core/director.h"
#include "core/scene.h"

#include "interface/input_delegate.h"
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
    
    void director::run_scene(const scene_ptr& scene)
    {
        if (m_scene)
            m_scene->on_exit();
        
        m_scene = scene;
        m_scene->on_enter();
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
        for (auto it : m_input_handlers)
        {
            if (it->on_mouse_down(location))
            {
                m_current_input = it;
                break;
            }
        }
	}

	void director::handle_mouse_move(const vector2d& location)
	{
        if (m_current_input)
            m_current_input->on_mouse_move(location);
	}

	void director::handle_mouse_up(const vector2d& location)
	{
        if (m_current_input)
            m_current_input->on_mouse_up(location);
	}
    
    void director::add_input_delegate(input_delegate* delegate)
    {
        m_input_handlers.push_back(delegate);
    }
    
    void director::remove_input_delegate(input_delegate* delegate)
    {
        auto it = std::find(m_input_handlers.begin(), m_input_handlers.end(), delegate);
        
        if (it != m_input_handlers.end())
            m_input_handlers.erase(it);
    }

	void director::update(float dt)
    {
		if (m_scene)
			m_scene->update(dt);
    }
}
