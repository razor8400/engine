#pragma once

#include "common.h"
#include "platform/window.h"

namespace engine
{
	class application;
	class window;
	
	class app_delegate
	{
	public:
		virtual void application_launched(application* application) = 0;
	};

	class application
	{
	public:
        static application& instance();
        
		void set_win_size(int width, int height);
		void set_display_name(const std::string& display_name);
		void set_delegate(app_delegate* delegate);

		void on_launched();
		bool run();
	private:
        application() {};
        
		std::string m_display_name;
		int m_width = 0, m_height = 0;

		app_delegate* m_delegate = nullptr;
		std::unique_ptr<window> m_window;
	};
}
