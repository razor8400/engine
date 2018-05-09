#include "common.h"
#include "resources/resources_manager.h"
#include "resources/font_ttf.h"
#include "label.h"

namespace engine
{   
    bool label::init(const std::string& font_name)
    {
        return init(font_name, 0);
    }
    
    bool label::init(const std::string& font_name, int font_size)
    {
        return init(font_name, font_size, empty_string);
    }
    
    bool label::init(const std::string& font_name, int font_size, const std::string& caption)
    {
        if (!sprite::init())
            return false;
        
        auto font = resources_manager::instance().load_resource_from_file<font_ttf>(font_name);
        
        if (!font)
            return false;
        
        m_font_size = font_size;
        m_caption = caption;

        set_font(font);
        update_texture();

        return true;
    }
    
    void label::set_font(const std::string& font_name)
    {
        auto font = resources_manager::instance().load_resource_from_file<font_ttf>(font_name);
        set_font(font);
    }
    
	void label::update_texture()
	{
		auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_font_position_color);
        
		if (m_font)
		{
            auto texture = m_font->create_label(m_caption, m_font_size, program);
			
            if (texture)
            {
                auto size = math::vector2d(texture->get_width(), texture->get_height());
				
                set_texture(texture, math::rect(0, 0, size.x, size.y));
                set_size(size);
            }
		}
	}
}
