#include "image_utils.h"
#include "libpng/png.h"

namespace engine
{
    namespace image_utils
    {
        bool read_png_data(texture2d::data* data, const unsigned char* buffer)
        {
            return true;
        }
        
        bool load_texture_data(texture2d::data* data, const unsigned char* buffer)
        {
            typedef std::function<bool(texture2d::data*, const unsigned char*)> format_helper;
            
            static const std::map<std::string, format_helper> helpers = {
                { format::png, read_png_data }
            };
            
            auto format = get_image_format(buffer);
            auto it = helpers.find(format);
            
            if (it != helpers.end())
                return it->second(data, buffer);
                
            return false;
        }
        
        const char* get_image_format(const unsigned char* buffer)
        {
            if (png_check_sig(buffer, 8))
                return format::png;
            
            return format::unknown;
        }
    }
}
