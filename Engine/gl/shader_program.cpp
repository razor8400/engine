#include "shader_program.h"

namespace gl
{
    const char* shader_program::shader_position_color = "shader_position_color";
    const char* shader_position_color::mvp = "mvp";
    
    shader_program::shader_program(GLuint program_id) : m_program_id(program_id)
    {
        
    }
    
    shader_program::~shader_program()
    {
        glDeleteProgram(m_program_id);
    }
    
    shader_position_color::shader_position_color(GLint program_id) : shader_program(program_id)
    {
        
    }
    
    void shader_position_color::apply_transform(const math::mat4& transform)
    {
        m_transform = transform;
    }
    
    void shader_position_color::use()
    {
        GLuint matrix_id = glGetUniformLocation(m_program_id, mvp);
        
        glUseProgram(m_program_id);
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &m_transform[0]);
    }
}

