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
    private:
        GLFWwindow* m_window = nullptr;
    };
}
