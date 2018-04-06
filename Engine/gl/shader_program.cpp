#include "shader_program.h"
#include "shaders.h"

namespace gl
{
    const char* shader_program::shader_position_color = "shader_position_color";
    const char* shader_program::shader_texture_position_color = "shader_texture_position_color";
    
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
    
    void shader_position_color::use(const math::mat4& transform)
    {
        GLuint matrix_id = glGetUniformLocation(m_program_id, shaders::mvp);
        
        glUseProgram(m_program_id);
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &transform[0]);
    }
    
    shader_texture_position_color::shader_texture_position_color(GLint program_id) : shader_program(program_id)
    {
        
    }
    
    void shader_texture_position_color::use(const math::mat4& transform)
    {
        GLuint matrix_id = glGetUniformLocation(m_program_id, shaders::mvp);
        GLuint texture_id  = glGetUniformLocation(m_program_id, shaders::texture_sampler2d);
        
        glUseProgram(m_program_id);
        
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &transform[0]);
        glUniform1i(texture_id, 0);
    }
}

