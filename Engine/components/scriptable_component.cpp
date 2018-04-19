#include "common.h"
#include "scriptable_component.h"

#include "resources/script.h"
#include "resources/resources_manager.h"

#include "core/director.h"

namespace engine
{
    IMPLEMENT_INHERITANCE_INFO(scriptable_component, component);
    
    scriptable_component* scriptable_component::create(const std::string& file_name)
    {
        auto resource = resources_manager::instance().load_resource_from_file<script>(file_name);
        
        if (resource)
        {
            auto component = ref::create<scriptable_component>();
            component->m_script = resource;
            return component;
        }
        
        return nullptr;
    }
    
    scriptable_component::~scriptable_component()
    {
        director::instance().remove_input_delegate(this);
    }
    
    void scriptable_component::start()
    {
        director::instance().add_input_delegate(this);
        
        if (m_script)
        {
			if (!m_script->run())
			{
				m_script.reset();
				return;
			}

            m_script->push_user_data("obj", m_parent);
            m_script->call_function(scripting::start);
        }
    }
    
    void scriptable_component::update(float dt)
    {
        if (m_script)
            m_script->call_function(scripting::update);
    }
    
    void scriptable_component::stop()
    {
        director::instance().remove_input_delegate(this);
        
        if (m_script)
        {
            m_script->call_function(scripting::stop);
            m_script->stop();
        }
    }
    
    void scriptable_component::on_mouse_down(const math::vector2d& location)
    {
        if (m_script)
        {
            m_script->push_vector("mouse", location);
            m_script->call_function(scripting::mouse_down);
        }
    }
    
    void scriptable_component::on_mouse_move(const math::vector2d& location)
    {
        if (m_script)
        {
            m_script->push_vector("mouse", location);
            m_script->call_function(scripting::mouse_move);
        }
    }
    
    void scriptable_component::on_mouse_up(const math::vector2d& location)
    {
        if (m_script)
        {
            m_script->push_vector("mouse", location);
            m_script->call_function(scripting::mouse_up);
        }
    }
}
