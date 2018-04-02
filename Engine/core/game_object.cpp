#include "game_object.h"

#include "gl/gl.h"
#include "gl/shaders.h"
#include "gl/shaders_manager.h"

namespace engine
{
	void game_object::update(float dt)
	{
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

		auto program = gl::shaders_manager::instance().get_program(gl::shaders::k_shader_position_color);
		program->apply_transform(world * transform());
		program->use();

		gl::draw_rect(vertices);
    }
    
    void game_object::on_enter()
    {
        for (auto obj : m_children)
            obj->on_enter();
        
        m_active = true;
    }
    
    void game_object::on_exit()
    {
        for (auto obj : m_children)
            obj->on_exit();
        
        m_active = false;
    }
    
	void game_object::add_child(game_object* obj)
	{
		obj->m_parent = this;
		m_children.push_back(obj);
	}

	void game_object::remove_child(game_object* obj)
	{
		auto it = std::find(m_children.begin(), m_children.end(), obj);

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

	math::mat4 game_object::transform() const
	{
		auto position = math::mat4::translate(m_position.x, m_position.y, m_position.z);
		auto rotation = math::mat4::rotate(m_rotation.x, m_rotation.y, m_rotation.z);
		auto scale = math::mat4::scale(m_scale.x, m_scale.y, m_scale.z);
		auto pivot = math::mat4::translate(m_anchor.x, m_anchor.y, m_anchor.z);

		return position;
	}
}
