#pragma once

#include "common.h"

namespace engine
{
	class file_utils
	{
	public:
		static file_utils& instance();

        std::string get_resources_folder() const;
        std::string get_path_to_resource(const std::string& path);
		bool read_file(const std::string& file_name, unsigned char* data) const;
	private:
		file_utils();
	};
}
