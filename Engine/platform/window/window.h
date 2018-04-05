#pragma once

#include "common.h"

namespace engine
{
    class window
    {
    public:
        window();
		bool create(const char* display_name, int width, int height);
		void process();
        const math::vector2d& get_win_size() const { return m_size; }
    private:
		math::vector2d m_size;
    };
}
