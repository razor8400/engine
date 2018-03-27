#pragma once

#include "common.h"

class GLFWwindow;

namespace engine
{
    class window
    {
    public:
        window(const char* display_name, int width, int height);
        void begin_render();
    private:
        GLFWwindow* m_window = nullptr;
    };
}
