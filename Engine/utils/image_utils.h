#pragma once

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
		struct image_data
		{
			int width;
			int height;
			int format;
		};
		
		bool load_texture_data(image_data* data, const unsigned char* buffer);
        const char* get_image_format(const unsigned char* buffer);
    }
}
