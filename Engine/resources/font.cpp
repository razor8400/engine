#include "common.h"
#include "font.h"

#include "ft2build.h"
#include FT_FREETYPE_H 

namespace engine
{
	std::shared_ptr<font> font::load_from_file(const std::string& file_name)
	{
		logger() << "[font] load font:" << file_name;

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			logger() << "[font] could not init FreeType library";
			return std::shared_ptr<font>();
		}

		FT_Face face;
		if (FT_New_Face(ft, file_name.c_str(), 0, &face))
		{
			logger() << "[font] failed to load font";
			return std::shared_ptr<font>();
		}

		return std::shared_ptr<font>();
	}
}