#pragma once

#include "common.h"

namespace engine
{   
	class scene;

    class director
    {
    public:
        static director& instance();
        
		void set_frame_rate(int frame_rate);
        void start(scene* scene);
        void stop();

		void main_loop();
		void handle_mouse_down(const vector2d& location);
		void handle_mouse_move(const vector2d& location);
		void handle_mouse_up(const vector2d& location);
	private:
        director();
        ~director();
        void update(float dt);
    private:
        float m_time_interval = 0;
        bool m_running = false;
		scene* m_scene = nullptr;
    };
}
