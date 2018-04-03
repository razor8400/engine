#pragma once

#include "common.h"

namespace engine
{
	class file_utils
	{
	public:
		static file_utils& instance();

		unsigned char* read_file(const std::string& file_name) const;
	private:
		file_utils();
	};
}