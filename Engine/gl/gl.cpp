#include "gl.h"

namespace engine
{
    namespace gl
    {
        bool init_gl()
        {
            glewExperimental = true;
            
            if (glewInit() != GLEW_OK)
                return false;
            
            return true;
        }
        
        GLint compile_shader(const char* source, unsigned int shader)
        {
            GLint result = GL_FALSE;
            int info_log_length = -1;
            
            GLuint shader_id = glCreateShader(shader);
            
            glShaderSource(shader_id, 1, &source , NULL);
            glCompileShader(shader_id);
            
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
            
            if (info_log_length > 0)
            {
                char* error_message = new char[info_log_length + 1];
                glGetShaderInfoLog(shader_id, info_log_length, NULL, error_message);
                fprintf(stdout, "%s", error_message);
                delete[] error_message;
            }
            
            return shader_id;
        }
        
        GLuint create_gl_program(const char* vert, const char* frag)
        {
            GLint result = GL_FALSE;
            int info_log_length = -1;
            
            GLuint vertex_shader = compile_shader(vert, GL_VERTEX_SHADER);
            GLuint fragment_shader = compile_shader(frag, GL_FRAGMENT_SHADER);
            
            GLuint program = glCreateProgram();
            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);
            
            // Проверяем шейдерную программу
            glGetProgramiv(program, GL_LINK_STATUS, &result);
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
           
            if (info_log_length > 0)
            {
                char* error_message = new char[info_log_length + 1];
                glGetProgramInfoLog(program, info_log_length, NULL, error_message);
                fprintf(stdout, "%s", error_message);
                delete[] error_message;
            }
            
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            
            return program;
        }
    }
}
