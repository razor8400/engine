#pragma once

#include "common.h"

namespace engine
{
	namespace file_utils
	{
        std::string get_resources_folder();
        std::string get_path_to_resource(const std::string& path);
        bool file_exist(const std::string& file_name);
		bool read_file(const std::string& file_name, unsigned char** data);
	};
}
