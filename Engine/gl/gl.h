#pragma once

#include "common.h"

#include "GLEW/glew.h"

namespace engine
{
    namespace gl
    {
        bool init_gl();
        
        GLint compile_shader(const char* source, unsigned int shader);
        GLuint create_gl_program(const char* vert, const char* frag);
    }
}
