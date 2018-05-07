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
        bool load_glyph(const std::string& font_name, char ch, int size, font_utils::glyph* glyph) const;
        
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
    
    bool free_type_library::load_glyph(const std::string& font_name, char ch, int size, font_utils::glyph* glyph) const
    {
		if (!library_loaded())
			return false;
        
        auto it = m_loaded_fonts.find(font_name);
        
        if (it == m_loaded_fonts.end())
        {
            logger() << "[free type] font not loaded:" << font_name;
            return false;
        }
        
        auto face = it->second;
        
        FT_Set_Pixel_Sizes(face, 0, size);
        
        if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
        {
            logger() << "[free type] failed to load glyph:" << ch;
            return false;
        }
        
        glyph->texture_id = gl::load_texture(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED);
        glyph->advance = face->glyph->advance.x;
        glyph->size = math::vector2d((int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows);
        glyph->bearing = math::vector2d(face->glyph->bitmap_left, face->glyph->bitmap_top);
        
        return true;
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
        
        bool load_glyph(const std::string& font_name, char ch, int size, glyph* glyph)
        {
            return library.load_glyph(font_name, ch, size, glyph);
        }
        
        glyphs_map load_glyphs(const std::string& font_name, const std::string& text, int size)
        {
            glyphs_map map;
        
            for (auto ch : text)
            {
                glyph glyph;
                if (load_glyph(font_name, ch, size, &glyph))
                    map[ch] = glyph;
            }
            
            return map;
        }
        
        void unload_font(const std::string& font_name)
        {
            library.unload_font(font_name);
        }
    }
}
