#pragma once

namespace engine
{
    namespace font_utils
    {
        struct glyph
        {
			unsigned int ax; // advance.x
			unsigned int ay; // advance.y

			unsigned int bw; // bitmap.width;
			unsigned int bh; // bitmap.rows;

			unsigned int bl; // bitmap_left;
			unsigned int bt; // bitmap_top;
        };

		typedef std::map<char, glyph> glyphs_map;

		struct glyphs_atlas
		{
			int texture;
			math::vector2d size;
			glyphs_map glyphs;
		};
                
		bool load_font(const std::string& file_name, const std::string& font_name);
		void unload_font(const std::string& font_name);

		glyphs_atlas create_atlas(const std::string& font_name, int font_size, const std::string& text);
		math::vector2d text_size(const std::string& font_name, int font_size, const std::string& text);
    }
}
