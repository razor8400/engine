#pragma once

#include "common.h"

namespace engine
{
    class input_delegate;
	class renderer;
    
    class director
    {
    public:
        static director& instance();
        
		void set_frame_rate(int frame_rate);
		void set_projection_mode(projection_mode mode);
		
		void set_near_plane(float near_plane);
		void set_far_plane(float far_plane);
		void set_field_of_view(float field_of_view);

		void set_camera_position(const math::vector3d& position);

		void start();
        void stop();
				
        void run_scene(scene* scene);
        
		void main_loop();
		
        void handle_mouse_down(const math::vector2d& location);
		void handle_mouse_move(const math::vector2d& location);
		void handle_mouse_up(const math::vector2d& location);
        
        void add_input_delegate(input_delegate* delegate);
        void remove_input_delegate(input_delegate* delegate);
        
        scene* running_scene() const { return m_scene; }
	private:
        void update(float delta_time);
        
        director();
        ~director();
    private:
		float m_time_interval = 0;

		scene* m_scene;

		bool m_running = false;

        std::vector<input_delegate*> m_input_handlers;
		std::unique_ptr<renderer> m_renderer;
        input_delegate* m_current_input = nullptr;
    };
}
