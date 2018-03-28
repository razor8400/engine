#pragma once

#include "common.h"

struct GLFWwindow;

namespace engine
{
    class window
    {
    public:
        window();
		bool create(const char* display_name, int width, int height);
		void process();
		const vector2d& get_win_size() const { return m_size; }
    private:
        GLFWwindow* m_window = nullptr;
		vector2d m_size;
    };
}
