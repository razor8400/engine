#pragma once

#include "resource.h"
#include "utils/font_utils.h"

namespace engine
{
	class font_ttf : public resource
	{
	public:
        font_ttf(const std::string& font_name);
        ~font_ttf();
        
		static std::shared_ptr<font_ttf> load_from_file(const std::string& file_name);
        bool load(const unsigned char* data, size_t size) override { return true; }
        
        texture2d_ptr create_label(const std::string& string, int size, const gl::shader_program_ptr& program);
	private:
        void update_atlas(const std::string& string, int size);
        void render_text(const std::string& string, int size);
	private:
        std::string m_font_name;
        std::map<int, font_utils::glyphs_map> m_loaded_glyphs;
	};
}
