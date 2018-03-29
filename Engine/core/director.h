#pragma once

#include "common.h"

namespace engine
{
    class input_delegate;
    
    class director
    {
    public:
        static director& instance();
        
		void set_frame_rate(int frame_rate);
        void start();
        void stop();

        void run_scene(const scene_ptr& scene);
        
		void main_loop();
		
        void handle_mouse_down(const math::vector2d& location);
		void handle_mouse_move(const math::vector2d& location);
		void handle_mouse_up(const math::vector2d& location);
        
        void add_input_delegate(input_delegate* delegate);
        void remove_input_delegate(input_delegate* delegate);
        
        const scene_ptr& running_scene() const { return m_scene; }
	private:
        director();
        ~director();
        void update(float dt);
    private:
        float m_time_interval = 0;
        bool m_running = false;
		scene_ptr m_scene;
        
        std::vector<input_delegate*> m_input_handlers;
        input_delegate* m_current_input = nullptr;
    };
}
