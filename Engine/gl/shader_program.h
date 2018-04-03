#pragma once

#include "gl.h"

namespace gl
{
    class shader_program
    {
    public:
        static const char* shader_position_color;
        
        shader_program(GLuint program_id);
        virtual ~shader_program();
        
        virtual void apply_transform(const math::mat4& transform) = 0;
        virtual void use() = 0;
    protected:
        GLint m_program_id = -1;
    };
    
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

