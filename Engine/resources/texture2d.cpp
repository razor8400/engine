#include "common.h"
#include "texture2d.h"

namespace engine
{
    static const int texture_default_id = -1;
    
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
        std::vector<math::vector2d> vertices =
        {
            { 0, 0 },
            { 100.0f / (float)m_width, 0 },
            { 100.0f / (float)m_width, 100.0f / (float)m_height, },
            { 0, 100.0f / (float)m_height }
        };
        
        std::vector<math::vector2d> uv =
        {
            { 0, 0 },
            { 1, 0,},
            { 1, 1 },
            { 0, 1 },
        };
        
        std::vector<GLushort> indices =
        {
            0, 1, 2, 2, 3, 0
        };
        
        //gl::bind_texture(m_texture_id);
        
        if (shader_program)
            shader_program->use(transform);
        
        gl::draw_texture2d(vertices, uv, indices);
    }
}
