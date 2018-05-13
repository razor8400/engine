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
        
        bool render_info(const std::string& text, int size, std::vector<gl::v3f_c4f_t2f>* vertices, int* texture);
        math::vector2d text_size(const std::string& text, int size) const;
    private:
        void update_atlas(const std::string& text, int size);
        const font_utils::atlas& get_atlas(const std::string& text, int size);
	private:
        std::string m_font_name;
		std::map<int, font_utils::atlas> m_cache;
	};
}
