#pragma once

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
                                            layout(location = 0) in vec3 vertex_position_modelspace;
                                            uniform mat4 mvp;
                                            void main()
                                            {
                                                gl_Position = mvp * vec4(vertex_position_modelspace, 1);
                                            })";

		static const char* shader_texture_color = R"(#version 330 core
												in vec2 uv;
												in vec4 color;
												out vec4 fragment_color;
												uniform sampler2D sampler2d;
												void main()
												{
                                                    fragment_color = vec4(1.0, 1.0, 1.0, texture(sampler2d, uv).r) * color;
												})";

		static const char* shader_texture_position = R"(#version 330 core
													layout(location = 0) in vec3 vertex_position_modelspace;
													layout(location = 1) in vec2 vertex_uv;
													layout (location = 2) in vec4 vertex_color;
													out vec2 uv;
													out vec4 color;
													uniform mat4 mvp;
													void main()
													{
													   gl_Position = mvp * vec4(vertex_position_modelspace, 1);
													   uv = vertex_uv;
													   color = vertex_color;	
													})";
        
        static const char* mvp = "mvp";
        static const char* texture_sampler2d = "sampler2d";
    }
}
