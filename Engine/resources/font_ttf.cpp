#include "common.h"
#include "utils/file_utils.h"
#include "font_ttf.h"

namespace engine
{
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
       
    texture2d_ptr font_ttf::create_label(int font_size, const std::string& string) const
    {
		if (string.empty())
			return texture2d_ptr();
		
		auto range = m_cache.equal_range(string);

		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.font_size == font_size)
				return it->second.atlas;
		}

		auto atlas = font_utils::create_atlas(m_font_name, font_size, string);
		auto texture = std::make_shared<texture2d>((int)atlas.size.x, (int)atlas.size.y, GL_RGBA);

		texture->set_texture_id(atlas.texture);

		m_cache.insert(std::make_pair(string, cache{ font_size, texture }));

		return texture;
    }
}
