#pragma once

#include "component.h"
#include "interface/input_delegate.h"

namespace engine
{
    class scriptable_component : public component, public input_delegate
    {
        DECLARE_CLASS;
    public:
        static scriptable_component* create(const std::string& file_name);
        
        ~scriptable_component();
        
        void start() override;
        void update(float dt) override;
        void stop() override;
        
        void on_mouse_down(const math::vector2d& location) override;
        void on_mouse_move(const math::vector2d& location) override;
        void on_mouse_up(const math::vector2d& location) override;
    private:
        script_ptr m_script;
    };
}
