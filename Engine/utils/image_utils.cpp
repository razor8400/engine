#include "common.h"

#include "image_utils.h"
#include "libpng/png.h"

namespace engine
{
	namespace png
	{
		static size_t bytes_read = 0;

		void read_png_callback(png_structp png_ptr, png_bytep out_data, png_size_t length)
		{
			unsigned char* data = (unsigned char*)png_get_io_ptr(png_ptr);
			
			memcpy(out_data, data + bytes_read, length);

			bytes_read += length;
		}

		bool read_png_data(image_utils::image_data* data, const unsigned char* buffer)
		{
			auto png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (!png_ptr)
				return false;

			auto info_ptr = png_create_info_struct(png_ptr);

			if (!info_ptr)
				return false;

			bytes_read = 0;

			png_set_read_fn(png_ptr, (png_voidp*)buffer, read_png_callback);
			png_read_info(png_ptr, info_ptr);

			data->width = png_get_image_width(png_ptr, info_ptr);
			data->height = png_get_image_height(png_ptr, info_ptr);
			data->format = png_get_color_type(png_ptr, info_ptr);
            data->bit_depth = png_get_bit_depth(png_ptr, info_ptr);

			return true;
		}
	}

    namespace image_utils
    {       
        bool load_texture_data(image_data* data, const unsigned char* buffer)
        {
            typedef std::function<bool(image_data*, const unsigned char*)> format_helper;
            
            static const std::map<std::string, format_helper> helpers =
            {
                { format::png, png::read_png_data }
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
