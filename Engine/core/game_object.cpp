#include "core/game_object.h"

namespace engine
{
	void game_object::update(float dt)
	{
		for (auto obj : m_children)
			obj->update(dt);
	}

	void game_object::draw()
	{
		for (auto obj : m_children)
			obj->draw();
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
}