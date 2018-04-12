#include "common.h"

#include "platform/file_system/file_system.h"

#include "image_utils.h"
#include "libpng/png.h"

namespace engine
{
	namespace png
	{
		bool read_png_data(image_utils::image_data* data, FILE* file)
		{
			auto png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (!png_ptr)
				return false;

			auto info_ptr = png_create_info_struct(png_ptr);

			if (!info_ptr)
				return false;
            
            if (setjmp(png_jmpbuf(png_ptr)))
                return false;

            png_init_io(png_ptr, file);
            
			png_read_info(png_ptr, info_ptr);

			data->width = png_get_image_width(png_ptr, info_ptr);
			data->height = png_get_image_height(png_ptr, info_ptr);
			data->format = png_get_color_type(png_ptr, info_ptr);
            data->bit_depth = png_get_bit_depth(png_ptr, info_ptr);
            
            auto buffer = new png_bytep[sizeof(png_bytep) * data->height];
            
            for (int y = 0; y < data->height; y++)
                buffer[y] = new png_byte[png_get_rowbytes(png_ptr, info_ptr)];
            
            png_read_image(png_ptr, buffer);
            
            for (int y = 0; y < data->height; ++y)
            {
                auto i = buffer[y];
                auto x = 0;
            }
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            
			return true;
		}
	}

    namespace image_utils
    {
        typedef std::function<bool(image_utils::image_data*, FILE*)> helper;
        
        bool load_image_from_file(const std::string& file_name, image_data* data)
        {
            auto format = get_image_format(file_name);
            
            std::map<std::string, helper> helpers =
            {
                { format::png, png::read_png_data }
            };
            
            auto it = helpers.find(format);
            
            if (it == helpers.end())
            {
                data->error = "unknown format";
                return false;
            }
            
            auto file = file_system::open_file(file_name.c_str(), "rb");
            
            if (file)
            {
                bool result =  it->second(data, file);
                
                fclose(file);
                
                return result;
            }
            
            data->error = "can't open file:" + file_name;
            return false;
        }
        
        std::string get_image_format(const std::string& file_name)
        {
            auto i = file_name.find_last_of('.');
            
            if (i != std::string::npos)
                return file_name.substr(i + 1);
            
            return format::unknown;
        }
    }
}
