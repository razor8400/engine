#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>

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
	GLuint load_texture(unsigned char* data, int width, int height, GLuint format);

    void draw_poly(const std::vector<math::vector2d>& vertices, const std::vector<GLushort>& indices);
    void draw_rect(const std::vector<math::vector2d>& vertices);
}
