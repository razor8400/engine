#include "gl.h"
#include "shaders_manager.h"

namespace gl
{
    bool init_gl()
    {
        glewExperimental = true;
        
        if (glewInit() != GLEW_OK)
            return false;
        
        return true;
    }

	GLuint generate_vbo()
	{
		GLuint vertex_array;
		glGenVertexArrays(1, &vertex_array);
		glBindVertexArray(vertex_array);

		return vertex_array;
	}
    
	void clear_vbo(GLuint vbo)
	{
		glDeleteVertexArrays(1, &vbo);
	}

	void compile_shaders()
    {
        auto& manager = shaders_manager::instance();
        manager.compile_default_shaders();
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    
    GLint create_gl_program(const char* vert, const char* frag)
    {
        GLint result = GL_FALSE;
        int info_log_length = -1;
        
        GLuint vertex_shader = compile_shader(vert, GL_VERTEX_SHADER);
        GLuint fragment_shader = compile_shader(frag, GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

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

	GLuint load_texture(const unsigned char* data, int width, int height, GLuint format)
	{
		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		return texture;
	}
    
    void delete_texture(GLuint texture)
    {
        glDeleteTextures(1, &texture);
    }

    void draw_poly(const std::vector<math::vector2d>& vertices, const std::vector<GLushort>& indices)
    {
        GLuint element_buffer;

        glGenBuffers(1, &element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

        GLuint vertex_buffer;

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::vector2d), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_SHORT, NULL);

		glDeleteBuffers(1, &element_buffer);
		glDeleteBuffers(1, &vertex_buffer);

        glDisableVertexAttribArray(0);
    }

    void draw_rect(const std::vector<math::vector2d>& vertices)
    {
        static const std::vector<GLushort> indices = { 0, 1, 2, 2, 3, 0 };
        draw_poly(vertices, indices);
    }
}
