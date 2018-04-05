#pragma once

#include "platform/window/window.h"

namespace engine
{
	class app_delegate;

	class application
	{
	public:
        static application& instance();
        
		void set_win_size(int width, int height);
		void set_display_name(const std::string& display_name);
		void set_delegate(app_delegate* delegate);

		void on_launched();
		bool run();
        const math::vector2d& get_win_size() const { return m_win_size; }
	private:
        application() {};
        
		std::string m_display_name;
        math::vector2d m_win_size;

		app_delegate* m_delegate = nullptr;
		std::unique_ptr<window> m_window;
	};
}
