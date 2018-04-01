#pragma once

#include "common.h"

#include "GLEW/glew.h"

namespace engine
{
    namespace gl
    {
		class shader_program
		{
		public:
			shader_program(GLuint program_id) : m_program_id(program_id)
			{

			}

			virtual void apply_transform(const math::mat4& transform) = 0;
			virtual void use() = 0;
		protected:
			GLint m_program_id = -1;
		};

		typedef std::shared_ptr<shader_program> shader_program_ptr;

        bool init_gl();
		void compile_shaders();
		void clear();
        
		GLint create_gl_program(const char* vert, const char* frag);

		void draw_poly(const std::vector<math::vector2d>& vertices, const std::vector<GLushort>& indices);
		void draw_rect(const std::vector<math::vector2d>& vertices);
    }
}
