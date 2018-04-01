#pragma once

#include "gl.h"

namespace engine
{
	namespace gl
	{
		namespace shaders
		{
			static const char* k_shader_position_color = "shader_position_color";
		}

		class shader_position_color : public shader_program
		{
		public:
			static const char* mvp;

			shader_position_color(GLint program_id);
			
			virtual void apply_transform(const math::mat4& transform) override;
			virtual void use() override;
		private:
			math::mat4 m_transform;
		};
	}
}