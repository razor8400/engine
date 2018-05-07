#pragma once

namespace engine
{
    namespace font_utils
    {
        struct glyph
        {
            unsigned int texture_id;        // ID handle of the glyph texture
            long advance;                   // Offset to advance to next glyph
            math::vector2d size;            // Size of glyph
            math::vector2d bearing;         // Offset from baseline to left/top of glyph
        };
        
        typedef std::map<char, glyph> glyphs_map;
        
        bool load_font(const std::string& file_name, const std::string& font_name);
        bool load_glyph(const std::string& font_name, char ch, int size, glyph* glyph);
        glyphs_map load_glyphs(const std::string& font_name, const std::string& text, int size);
        
        void unload_font(const std::string& font_name);
    }
}
