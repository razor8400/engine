#include "file_utils.h"

namespace engine
{
	file_utils& file_utils::instance()
	{
		static file_utils utils;

		return utils;
	}

	unsigned char* file_utils::read_file(const std::string& file_name) const
	{
		return nullptr;
	}

	file_utils::file_utils()
	{

	}
}