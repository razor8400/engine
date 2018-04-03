#pragma once

#include "gl.h"

namespace engine
{
	namespace gl
	{
		namespace shaders
		{
			static const char* shader_color = R"(#version 330 core
												out vec3 color;
												void main()
												{
													color = vec3(1, 1, 1);
												})";

			static const char* shader_position = R"(#version 330 core
												layout(location = 0) in vec3 vertexPosition_modelspace;
												uniform mat4 mvp;
												void main()
												{
													gl_Position = mvp * vec4(vertexPosition_modelspace,1);
												})";

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