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
                                            layout(location = 0) in vec3 vertexPosition_modelspace;
                                            uniform mat4 mvp;
                                            void main()
                                            {
                                                gl_Position = mvp * vec4(vertexPosition_modelspace,1);
                                            })";
    }
}
