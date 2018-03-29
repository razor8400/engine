#include "game_object.h"

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
        {
            if (obj->m_z_order >= 0)
                obj->draw();
        }
        
        render();
        
        for (auto obj : m_children)
        {
            if (obj->m_z_order < 0)
                obj->draw();
        }
	}
    
    void game_object::render()
    {
        
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
        add_child(obj, get_children_count());
    }

	void game_object::add_child(game_object* obj, int z_order)
	{
		obj->m_parent = this;
        obj->m_z_order = z_order;
		m_children.push_back(obj);
        
        std::sort(m_children.begin(), m_children.end(), [](game_object* obj1, game_object* obj2)
        {
            return obj1->m_z_order > obj2->m_z_order;
        });
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
