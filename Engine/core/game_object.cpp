#include "common.h"

#include "components/component.h"
#include "game_object.h"

namespace engine
{
    IMPLEMENT_TYPE_INFO(game_object)
    
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
        
        m_components.lock([this, dt]()
        {
            for (auto component : m_components)
                component->update(dt);
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
        for (auto component : m_components)
            component->start();
        
        for (auto obj : m_children)
            obj->on_enter();
        
        m_active = true;

		mark_dirty();
    }
    
    void game_object::on_exit()
    {
        for (auto component : m_components)
            component->stop();
        
        for (auto obj : m_children)
            obj->on_exit();
        
        m_active = false;
    }
    
	void game_object::add_child(game_object* obj)
	{
        if (m_active)
            obj->on_enter();
        
		obj->m_parent = this;
		m_children.push_back(obj);
	}

	void game_object::remove_child(game_object* obj)
	{
        m_children.erase(obj);

        if (m_active)
            obj->on_exit();
        
        obj->m_parent = nullptr;
	}

	void game_object::remove_from_parent()
	{
		if (m_parent)
			m_parent->remove_child(this);
	}
    
    void game_object::add_component(component* component)
    {
        component->m_parent = this;
        
        if (m_active)
            component->start();
        
        m_components.push_back(component);
    }
    
    void game_object::remove_component(component* component)
    {
        if (m_active)
            component->stop();
        
        m_components.erase(component);
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
