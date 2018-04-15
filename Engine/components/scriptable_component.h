#pragma once

#include "component.h"

namespace engine
{
    class scriptable_component : public component
    {
    public:
        static scriptable_component* create(const std::string& file_name);
        
        void start() override;
        void update(float dt) override;
        void stop() override;
    private:
        script_ptr m_script;
    };
}
