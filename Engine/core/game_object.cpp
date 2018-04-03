#include "game_object.h"

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
		if (m_update_transform)
		{
			m_update_transform = false;
			m_transform = parent_transform();
		}

		for (auto obj : m_children)
			obj->update(dt);
	}

	void game_object::draw(const math::mat4& world)
	{ 
		for (auto obj : m_children)
			obj->draw(world);

        render(world);
    }
    
    void game_object::render(const math::mat4& world)
    {
		std::vector<math::vector2d> vertices = 
		{
			{ -m_size.x / 2, -m_size.y / 2, },
			{ m_size.x /2, -m_size.x /2, },
			{ m_size.x /2, m_size.y / 2, },
			{ -m_size.x / 2, m_size.y / 2 }
		};

		auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_position_color);
		program->apply_transform(world * world_transform());
		program->use();

		gl::draw_rect(vertices);
    }
    
    void game_object::on_enter()
    {
        for (auto obj : m_children)
            obj->on_enter();
        
        m_active = true;
		mark_dirty();
    }
    
    void game_object::on_exit()
    {
        for (auto obj : m_children)
            obj->on_exit();
        
        m_active = false;
    }
    
	void game_object::add_child(const game_object_ptr& obj)
	{
		obj->m_parent = this;
		m_children.push_back(obj);
	}

	void game_object::remove_child(game_object* obj)
	{
		auto it = std::find_if(m_children.begin(), m_children.end(), [obj](const game_object_ptr& ob)
		{
			return obj == ob.get();
		});

		if (it != m_children.end())
		{
			m_children.erase(it);
			obj->m_parent = nullptr;
		}
	}

	void game_object::remove_from_parent()
	{
		if (m_parent)
			m_parent->remove_child(this);
	}

	math::mat4 game_object::parent_transform() const
	{
		auto center = m_size * m_anchor;

		auto position = math::mat4::translate(m_position.x, m_position.y, m_position.z);
		auto rotation = math::mat4::rotate(math::vector3d::right, m_rotation.x)
			* math::mat4::rotate(math::vector3d::up, m_rotation.y)
			* math::mat4::rotate(math::vector3d(0, 0, 1), m_rotation.z);

		auto scale = math::mat4::scale(m_scale.x, m_scale.y, m_scale.z);
		auto pivot = math::mat4::translate(center.x, center.y, center.z);

		return position * pivot * scale * rotation * math::mat4::translate(-center.x, -center.y, -center.z);
	}

	math::mat4 game_object::world_transform() const
	{
		auto tr = transfrom();

		for (auto obj = m_parent; obj != nullptr; obj = obj->m_parent)
			tr *= obj->transfrom();

		return tr;
	}
}
