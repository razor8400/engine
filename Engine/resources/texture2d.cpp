#include "common.h"
#include "texture2d.h"
#include "utils/image_utils.h"

namespace engine
{
    static const int texture_default_id = -1;
    
    texture2d::~texture2d()
    {
        if (m_texture_id != texture_default_id)
            gl::delete_texture(m_texture_id);
    }
    
    bool texture2d::load(const unsigned char* data)
    {
		auto image = image_utils::image_data();
		if (image_utils::load_texture_data(&image, data))
        {
			m_width = image.width;
			m_height = image.height;
            m_texture_id = gl::load_texture(data, m_width, m_height, image.format);
            return true;
        }
        
        return false;
    }
}
