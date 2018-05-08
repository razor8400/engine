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

        return true;
    }
    
    void label::set_font(const std::string& font_name)
    {
        auto font = resources_manager::instance().load_resource_from_file<font_ttf>(font_name);
        
        if (font)
            set_font(font);
    }

	void label::render(const math::mat4& tr)
	{
		if (m_update_texture)
		{
			m_update_texture = false;
			update_texture(tr);
		}
		auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_font_position_color);

		//m_font->render_text(m_caption, m_font_size, tr, program);

		if (m_texture)
			m_quad = update_quad();

		sprite::render(tr);
	}
    
	void label::update_texture(const math::mat4& tr)
	{
		auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_font_position_color);
		auto transform = parent_transform();
		
		clear_texture();

		if (m_font)
		{
			auto texture = m_font->create_label(m_caption, m_font_size, tr, program);
			
			if (texture)
			{
				auto size = math::vector2d(texture->get_width(), texture->get_height());
				
				set_texture(texture, math::rect(0, 0, size.x, size.y));
				set_size(size);
			}
		}
	}
}
