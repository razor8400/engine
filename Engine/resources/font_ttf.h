#pragma once

#include "resource.h"
#include "utils/font_utils.h"

namespace engine
{
	class font_ttf : public resource
	{
	private:
		struct cache
		{
			int font_size;
			texture2d_ptr atlas;
		};
	public:
        font_ttf(const std::string& font_name);
        ~font_ttf();
        
		static std::shared_ptr<font_ttf> load_from_file(const std::string& file_name);
        bool load(const unsigned char* data, size_t size) override { return true; }
        
		texture2d_ptr create_label(int font_size, const std::string& string) const;
	private:
        std::string m_font_name;
		mutable std::multimap<std::string, cache> m_cache;
	};
}
