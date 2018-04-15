#include "common.h"
#include "utils/image_utils.h"
#include "texture2d.h"

namespace engine
{
    static const int texture_default_id = -1;
    
    texture2d_ptr texture2d::load_from_file(const std::string& file_name)
    {
        auto data = image_utils::image_data();
        
        if (image_utils::load_image_from_file(file_name, &data))
        {
            auto texture = std::make_shared<texture2d>(data.width, data.height, data.format);
            texture->load(data.buffer);
            
            return texture;
        }
        
        log(data.error.c_str());
        
        return texture2d_ptr();
    }
    
    texture2d::texture2d(int width, int height, int format) : m_width(width), m_height(height), m_format(format)
    {
        
    }
    
    texture2d::~texture2d()
    {
        if (m_texture_id != texture_default_id)
            gl::delete_texture(m_texture_id);
    }
    
    void texture2d::load(const unsigned char* data)
    {
        m_texture_id = gl::load_texture(data, m_width, m_height, m_format);
    }
    
    void texture2d::draw(const math::mat4& transform, const gl::shader_program_ptr& shader_program)
    {
        gl::bind_texture(m_texture_id);
        gl::set_blend_func(m_blend_func.source, m_blend_func.destination);
        
        if (shader_program)
            shader_program->use(transform, m_color);
        
        gl::draw_texture2d(0, 0, m_width, m_height);
    }
}
