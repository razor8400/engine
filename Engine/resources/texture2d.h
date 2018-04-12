#pragma once

#include "resource.h"

namespace engine
{
    class texture2d : public resource
	{
    public:
        texture2d(int width, int height, int format);
        virtual ~texture2d();
        
        void load(const unsigned char* data) override;
        void draw(const math::mat4& transform, const gl::shader_program_ptr& shader_program);
        
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
    private:
		int m_width = 0;
		int m_height = 0;
        int m_format = 0;
        int m_texture_id = -1;
	};
}
