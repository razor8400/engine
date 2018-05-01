#pragma once

#include "common.h"

namespace engine
{
	class renderer;
    
    class director
    {
    public:
        static director& instance();
        
        math::vector3d convert_screen_to_world(const math::vector2d& screen) const;
        
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
        
        scene* running_scene() const { return m_scene; }
	private:
        void update(float delta_time);
        
        director();
        ~director();
    private:
		float m_time_interval = 0;

        scene* m_scene = nullptr;
        scene* m_next_scene = nullptr;

		bool m_running = false;

		std::unique_ptr<renderer> m_renderer;
    };
}
