#include "common.h"
#include "utils/file_utils.h"
#include "font_ttf.h"

namespace engine
{
	static const std::vector<math::vector2d> uv =
	{
		math::vector2d(0, 1),
		math::vector2d(1, 1),
		math::vector2d(1, 0),
		math::vector2d(0, 0)
	};

	static const std::vector<math::vector4d> colors =
	{
		math::vector4d(1, 1, 1, 1),
		math::vector4d(1, 1, 1, 1),
		math::vector4d(1, 1, 1, 1),
		math::vector4d(1, 1, 1, 1)
	};

    font_ttf::font_ttf(const std::string& font_name) : m_font_name(font_name)
    {
        
    }
    
    font_ttf::~font_ttf()
    {
        font_utils::unload_font(m_font_name);
    }
    
	std::shared_ptr<font_ttf> font_ttf::load_from_file(const std::string& file_name)
	{
		logger() << "[font_ttf] load:" << file_name;

        auto font_name = file_utils::get_file_name(file_name);
        
        if (font_utils::load_font(file_name, font_name))
            return std::make_shared<font_ttf>(font_name);
        
		return std::shared_ptr<font_ttf>();
	}
    
    void font_ttf::update_atlas(const std::string& string, int size)
    {
        auto it = m_loaded_glyphs.find(size);
        
        if (it == m_loaded_glyphs.end())
            m_loaded_glyphs[size] = font_utils::load_glyphs(m_font_name, string, size);
        
        auto& glyphs = m_loaded_glyphs[size];
        
        for (auto& ch : string)
        {
            if (glyphs.find(ch) != glyphs.end())
                continue;
            
            font_utils::glyph glyph;
            if (font_utils::load_glyph(m_font_name, ch, size, &glyph))
                glyphs[ch] = glyph;
        }
    }
    
    void font_ttf::draw_string(const std::string& string, int size, const math::mat4& world, const gl::shader_program_ptr& program)
    {
        if (string.empty())
            return;
        
		update_atlas(string, size);
        
        auto& glyphs = m_loaded_glyphs[size];
        
        int x = 0;
        
        for (auto& ch : string)
        {
            auto it = glyphs.find(ch);
            
            if (it == glyphs.end())
                continue;
            
            gl::bind_texture(it->second.texture_id);
            gl::set_blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            program->use(world);
            
            auto px = x + it->second.bearing.x;
            auto py = it->second.size.y - it->second.bearing.y;
            
            auto w = it->second.size.x;
            auto h = it->second.size.y;
            
            std::vector<math::vector2d> vertices =
            {
                math::vector2d(px, py),
                math::vector2d(px + w, py),
                math::vector2d(px + w, py + h),
                math::vector2d(px, py + h)
            };
                        
            gl::draw_texture2d(vertices, uv, colors);
            
            x += it->second.advance >> 6;
        }
    }
}
