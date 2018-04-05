#pragma once

#include "common.h"
#include "texture2d.h"

namespace engine
{
    namespace format
    {
        static const char* png = "png";
        static const char* jpeg = "jpg";
        static const char* pvr4 = "pvr4";
        static const char* unknown = "unknown";
    }
    
    namespace image_utils
    {
        bool load_texture_data(texture2d::data* data, const unsigned char* buffer);
        const char* get_image_format(const unsigned char* buffer);
    }
}
