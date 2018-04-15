#include "common.h"
#include "game_object.h"

#include "actions/action.h"
#include "resources/script.h"

namespace engine
{
	bool game_object::init()
	{
		m_scale = math::vector3d(1.0f, 1.0f, 1.0f);
		m_anchor = math::vector3d(0.5f, 0.5f, 0.5f);
        
		return true;
	}

	void game_object::update(float dt)
	{
        if (!m_enabled)
            return;
        
		if (m_update_transform)
		{
			m_update_transform = false;
			m_transform = parent_transform();
		}
        
        m_actions.lock([this, dt]()
        {
           for (auto action : m_actions)
               action->update(dt);
        });
        
        m_scritps.lock([this]()
        {
            for (auto script : m_scritps)
                script->call_function(scripting::update);
        });
        
        m_children.lock([this, dt]()
        {
            for (auto obj : m_children)
                obj->update(dt);
        });
	}

	void game_object::draw(const math::mat4& world)
	{
        render(world);
        
		for (auto obj : m_children)
			obj->draw(world);
    }
    
    void game_object::render(const math::mat4& world)
    {
#if DEBUG_DRAW
        auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_position_color);
        
        if (program)
            program->use(transfrom(world), math::vector4d::one);

        gl::draw_rect(0, 0, m_size.x, m_size.y);
#endif
    }
    
    void game_object::on_enter()
    {
        for (auto obj : m_children)
            obj->on_enter();
        
        for (auto script : m_scritps)
            script->run(this);
        
        m_active = true;

		mark_dirty();
    }
    
    void game_object::on_exit()
    {
        for (auto obj : m_children)
            obj->on_exit();
        
        for (auto script : m_scritps)
            script->call_function(scripting::stop);
        
        m_active = false;
    }
    
	void game_object::add_child(const game_object_ptr& obj)
	{
        if (!obj)
            return;
        
        if (m_active)
            obj->on_enter();
        
		obj->m_parent = this;
		m_children.push_back(obj);
	}

	void game_object::remove_child(game_object* obj)
	{
        if (!obj)
            return;
        
		auto it = std::find_if(m_children.begin(), m_children.end(), [obj](const game_object_ptr& ob)
		{
			return obj == ob.get();
		});

		if (it != m_children.end())
		{
            if (m_active)
                obj->on_exit();
            
            m_children.erase(it);
			obj->m_parent = nullptr;
		}
	}

	void game_object::remove_from_parent()
	{
		if (m_parent)
			m_parent->remove_child(this);
	}
    
    void game_object::run_action(const action_ptr& action)
    {
        if (!action)
            return;
        
        action->start(this);
        m_actions.push_back(action);
    }
    
    void game_object::on_action_done(action* action)
    {
        auto it = std::find_if(m_actions.begin(), m_actions.end(), [action](const action_ptr& ptr)
        {
           return ptr.get() == action;
        });
        
        if (it != m_actions.end())
        {
            action->finish();
            m_actions.erase(it);
        }
    }
    
    void game_object::run_script(const script_ptr& script)
    {
        if (!script)
            return;
        
        if (m_active)
            script->run(this);
        
        m_scritps.push_back(script);
    }
    
    math::mat4 game_object::transfrom(const math::mat4& parent) const
    {
        auto anchor = m_size * m_anchor;
        return parent * world_transform() * math::mat4::translate(-anchor.x, -anchor.y, -anchor.z);
    }

	math::mat4 game_object::parent_transform() const
	{
		auto position = math::mat4::translate(m_position.x, m_position.y, m_position.z);
		auto rotation = math::mat4::rotate(math::vector3d::right, m_rotation.x)
			* math::mat4::rotate(math::vector3d::up, m_rotation.y)
			* math::mat4::rotate(math::vector3d(0, 0, 1), m_rotation.z);

		auto scale = math::mat4::scale(m_scale.x, m_scale.y, m_scale.z);
        
        return position * rotation * scale;
    }

	math::mat4 game_object::world_transform() const
	{
		auto tr = m_transform;

		for (auto obj = m_parent; obj != nullptr; obj = obj->m_parent)
			tr *= obj->m_transform;

		return tr;
	}
}
