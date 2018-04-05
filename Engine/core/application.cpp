#include "common.h"
#include "application.h"
#include "interface/app_delegate.h"

namespace engine
{
    application& application::instance()
    {
        static application instance;
        return instance;
    }
    
	void application::set_win_size(int width, int height)
	{
		m_win_size.x = (float)width;
		m_win_size.y = (float)height;
	}

	void application::set_display_name(const std::string& display_name)
	{
		m_display_name = display_name;
	}

	void application::set_delegate(app_delegate* delegate)
	{
		m_delegate = delegate;
	}

	void application::on_launched()
	{
		if (m_delegate)
			m_delegate->application_launched(this);
	}

	bool application::run()
	{
		m_window = std::make_unique<window>();

		if (!m_window->create(m_display_name.c_str(), (int)m_win_size.x, (int)m_win_size.y))
			return false;

		m_window->process();

		return true;
	}
}

