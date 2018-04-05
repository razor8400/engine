#include "file_utils.h"
#include "platform/file_system/file_system.h"

#include <stdio.h>

namespace engine
{
    namespace file_utils
    {
        static const char* assets_folder = "Assets/";
        
        bool read_file(const std::string& file_name, unsigned char** data)
        {
            auto file = fopen(file_name.c_str(), "r+");
            
            if (file != NULL)
            {
                fseek(file, 0, SEEK_END);
                
                auto size = ftell(file);
                *data = new unsigned char[size];
                
                fseek(file, 0, 0);
                
                auto bytes_read = fread(*data, sizeof(unsigned char), size, file);
                
                fclose(file);
                
                return bytes_read == size;
            }
            
            return false;
        }
        
        std::string get_resources_folder()
        {
            return file_system::get_current_directory() + '/' + assets_folder;
        }
        
        std::string get_path_to_resource(const std::string& path)
        {
            return get_resources_folder() + path;
        }
    }
}