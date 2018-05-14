#include "common.h"
#include "utils/file_utils.h"
#include "font_ttf.h"

namespace engine
{
    static const int max_atlas = 1024;
    
    font_ttf::font_ttf(const std::string& font_name) : m_font_name(font_name)
    {
        
    }
    
    font_ttf::~font_ttf()
    {
        for (auto& it : m_cache)
            gl::delete_texture(it.second.texture);
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
    
    bool font_ttf::render_info(const std::string& text, int size, 
								vertical_text_alignment vertical_alignment, horisontal_text_alignment horisontal_alignmen,
								std::vector<gl::v3f_c4f_t2f>* vertices, int* texture)
    {
        if (text.empty())
            return false;
        
        auto& atlas = get_atlas(text, size);
        
        *texture = atlas.texture;
        
        int x = 0;
        int y = atlas.height;
        
        for (auto& ch : text)
        {
			if (ch == '\n')
			{
				y -= size;
				x = 0;
				continue;
			}

            auto it = atlas.glyphs.find(ch);
            
            if (it == atlas.glyphs.end())
                continue;
            
            auto& glyph = it->second;
            
            float tx = glyph.tx;
            float ty = glyph.ty;
            
            auto quad = gl::v3f_c4f_t2f_quad();
            
            quad[gl::bottom_left].vertice = { x + glyph.bl, y + glyph.bt, 0 };
            quad[gl::bottom_right].vertice = { x + glyph.bl + glyph.bw, y + glyph.bt, 0 };
            quad[gl::top_right].vertice = { x + glyph.bl + glyph.bw, y + glyph.bt - glyph.bh, 0 };
            quad[gl::top_left].vertice = { x + glyph.bl, y + glyph.bt - glyph.bh, 0 };
            
            quad[gl::bottom_left].tex_coord = { tx, ty };
            quad[gl::bottom_right].tex_coord = { tx + (float)glyph.bw / atlas.width, ty };
            quad[gl::top_right].tex_coord = { tx + (float)glyph.bw / atlas.width, ty + ((float)glyph.bh / atlas.height) };
            quad[gl::top_left].tex_coord = { tx, ty + ((float)glyph.bh / atlas.height) };
            
            vertices->insert(vertices->end(), quad.begin(), quad.end());
            
            x += glyph.ax;
        }
        
        return true;
    }
    
    const font_utils::atlas& font_ttf::get_atlas(const std::string& text, int size)
    {
        auto it = m_cache.find(size);
        
        if (it != m_cache.end())
        {
            auto& glyphs = it->second.glyphs;
            std::string buffer;
            for (auto& ch : text)
            {
                if (glyphs.find(ch) != glyphs.end())
                    continue;
                
                buffer.push_back(ch);
            }
            
            if (buffer.size() > 0)
                update_atlas(buffer, size);
        }
        else
        {
            update_atlas(text, size);
        }
        
        return m_cache[size];
    }
    
    void font_ttf::update_atlas(const std::string& text, int size)
    {
        auto& atlas = m_cache[size];
        std::string buffer;
        
        for (auto& it : atlas.glyphs)
            buffer.push_back(it.first);
        
        buffer.insert(buffer.end(), text.begin(), text.end());
        
        m_cache[size] = font_utils::create_atlas(m_font_name, size, buffer, max_atlas);
    }
    
    math::vector2d font_ttf::text_size(const std::string& text, int size, int max_line_width) const
    {
        auto sz = font_utils::text_size(m_font_name, size, text, max_line_width);
        return math::vector2d(sz.w, sz.h);
    }
}
