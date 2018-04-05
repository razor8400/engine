#pragma once

#include <vector>
#include <map>
#include <string>

#include "math/libmath.h"

#include "GLEW/glew.h"

namespace gl
{
    bool init_gl();

	GLuint generate_vbo();

	void clear_vbo(GLuint vbo);
    void compile_shaders();
    void clear();
    
    GLint create_gl_program(const char* vert, const char* frag);
	GLuint load_texture(const unsigned char* data, int width, int height, GLuint format);
    
    void delete_texture(GLuint texture);

    void draw_poly(const std::vector<math::vector2d>& vertices, const std::vector<GLushort>& indices);
    void draw_rect(const std::vector<math::vector2d>& vertices);
}
