#include "common.h"
#include "font_utils.h"

#include "ft2build.h"
#include FT_FREETYPE_H 

namespace engine
{
    class free_type_library
    {
    public:
        free_type_library();
        ~free_type_library();
        
		bool library_loaded() const;
        bool load_font(const std::string& file_name, const std::string& font_name) const;
		font_utils::glyphs_map load_glyphs(const std::string& font_name, int font_size, const std::string& text, int texture) const;
        
		math::vector2d text_size(const std::string& font_name, int font_size, const std::string& text) const;
        void unload_font(const std::string& font_name);
    private:
        FT_Library m_libary;
        bool m_library_loaded = true;
        mutable std::map<std::string, FT_Face> m_loaded_fonts;
    };
    
    free_type_library::free_type_library()
    {
        logger() << "[free_type] load library";
        
        if (FT_Init_FreeType(&m_libary))
        {
            logger() << "[free_type] could not init FreeType library";
            m_library_loaded = false;
        }
    }
    
    free_type_library::~free_type_library()
    {
        logger() << "[free_type] unload library";
        
        if (m_library_loaded)
        {
            for (auto it : m_loaded_fonts)
                FT_Done_Face(it.second);
            
            FT_Done_FreeType(m_libary);
        }
    }

	bool free_type_library::library_loaded() const
	{
		if (!m_library_loaded)
		{
			logger() << "[free type] library not loaded";
			return false;
		}

		return true;
	}
    
    bool free_type_library::load_font(const std::string& file_name, const std::string& font_name) const
    {
		if (!library_loaded())
			return false;
        
        auto it = m_loaded_fonts.find(font_name);
        
        if (it == m_loaded_fonts.end())
        {
            FT_Face face;
            
            logger() << "[free type] load font:" << font_name;
            
            if (FT_New_Face(m_libary, file_name.c_str(), 0, &face))
                return false;
            
            m_loaded_fonts[font_name] = face;
        }
        
        return true;
    }

	font_utils::glyphs_map free_type_library::load_glyphs(const std::string& font_name, int font_size, const std::string& text, int texture) const
	{
		auto map = font_utils::glyphs_map();

		if (!library_loaded())
			return map;

		auto it = m_loaded_fonts.find(font_name);

		if (it == m_loaded_fonts.end())
		{
			logger() << "[free type] font not loaded:" << font_name;
			return map;
		}

		auto face = it->second;
		FT_Set_Pixel_Sizes(face, 0, font_size);

		int x = 0;

		for (auto& ch : text)
		{
			if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
			{
				logger() << "[free type] failed to load glyph:" << ch;
				continue;
			}

			auto glyph = font_utils::glyph();
			auto ft = face->glyph;

			glyph.ax = ft->advance.x >> 6;
			glyph.ay = ft->advance.y >> 6;
			glyph.bw = ft->bitmap.width; 
			glyph.bh = ft->bitmap.rows;
			glyph.bl = ft->bitmap_left;
			glyph.bt = ft->bitmap_top;

			gl::sub_image2d(texture, GL_TEXTURE_2D, 0, x, 0, glyph.bw, glyph.bh, GL_RED, GL_UNSIGNED_BYTE, ft->bitmap.buffer);

			x += ft->bitmap.width;

			map[ch] = glyph;
		}

		return map;
	}
        
	math::vector2d free_type_library::text_size(const std::string& font_name, int font_size, const std::string& text) const
	{
		if (!library_loaded())
			return math::vector2d::zero;

		auto it = m_loaded_fonts.find(font_name);

		if (it == m_loaded_fonts.end())
		{
			logger() << "[free type] font not loaded:" << font_name;
			return math::vector2d::zero;
		}

		auto face = it->second;
		
		int w = 0;
		int h = 0;

		for (auto& ch : text)
		{
			FT_Set_Pixel_Sizes(face, 0, font_size);

			if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
			{
				logger() << "[free type] failed to load glyph:" << ch;
				continue;
			}

			auto glyph = face->glyph;

			w += glyph->advance.x >> 6;
			h = std::max(h, (int)face->glyph->bitmap.rows);
		}
		
		return math::vector2d(w, h);

	}

	void free_type_library::unload_font(const std::string& font_name)
    {
        logger() << "[free type] unload font:" << font_name;
        
		if (!library_loaded())
			return;
        
        auto it = m_loaded_fonts.find(font_name);
        
        if (it != m_loaded_fonts.end())
        {
			FT_Done_Face(it->second);
			m_loaded_fonts.erase(it);
        }      
    }
    
    namespace font_utils
    {
        static free_type_library library;

		bool load_font(const std::string& file_name, const std::string& font_name)
        {
            if (!library.load_font(file_name, font_name))
            {
                logger() << "[font utils] error loading font:" << font_name;
                return false;
            }
            
            return true;
        }
                        
        void unload_font(const std::string& font_name)
        {
            library.unload_font(font_name);
        }
		
		glyphs_atlas create_atlas(const std::string& font_name, int font_size, const std::string& text)
		{
			auto atlas = glyphs_atlas();
			auto size = text_size(font_name, font_size, text);

			atlas.texture = gl::load_texture(0, (int)size.x, (int)size.y, GL_RED);
			atlas.glyphs = library.load_glyphs(font_name, font_size, text, atlas.texture);
			atlas.size = size;

			return atlas;
		}

		math::vector2d text_size(const std::string& font_name, int font_size, const std::string& text)
		{
			return library.text_size(font_name, font_size, text);
		}
    }
}
