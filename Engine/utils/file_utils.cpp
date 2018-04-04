#include "file_utils.h"
#include "platform/file_system.h"

namespace engine
{
    static const char* assets_folder = "Assets/";
    
	file_utils& file_utils::instance()
	{
		static file_utils utils;

		return utils;
	}

	bool file_utils::read_file(const std::string& file_name, unsigned char* data) const
	{
		return nullptr;
	}
    
    std::string file_utils::get_resources_folder() const
    {
        return file_system::get_current_directory() + '/' + assets_folder;
    }
    
    std::string file_utils::get_path_to_resource(const std::string& path)
    {
        return get_resources_folder() + path;
    }

	file_utils::file_utils()
	{

	}
}
