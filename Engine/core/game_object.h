#pragma once

#include "common.h"

namespace engine
{
	class game_object
	{
	public:
        virtual bool init() { return true; }
        
		virtual void update(float dt);
		virtual void draw(const math::mat4& world);
        virtual void render(const math::mat4& world);
        
        virtual void on_enter();
        virtual void on_exit();

        virtual void add_child(game_object* obj);
		virtual void remove_child(game_object* obj);
		virtual void remove_from_parent();

		math::mat4 transform() const;
    public:
		void set_position(const math::vector3d& position) { m_position = position; }
		const math::vector3d& get_position() const { return m_position; }

		void set_rotation(const math::vector3d& rotation) { m_rotation = rotation; }
		const math::vector3d& get_rotation() const { return m_rotation; }

		void set_scale(const math::vector3d& scale) { m_scale = scale; }
		const math::vector3d& get_scale() const { return m_scale; }

		void set_size(const math::vector3d& size) { m_size = size; }
		const math::vector3d& get_size() const { return m_size; }

		void set_anchor(const math::vector3d& anchor) { m_anchor = anchor; }
		const math::vector3d& get_anchor() const { return m_anchor; }

		void set_tag(int tag) { m_tag = tag; }
		int get_tag() const { return m_tag; }
                
        int get_children_count() const { return (int)m_children.size(); }
	protected:
		std::vector<game_object*> m_children;

		math::vector3d m_position;
		math::vector3d m_rotation;
		math::vector3d m_scale;
		math::vector3d m_size;
        math::vector3d m_anchor = math::vector3d(0.5f, 0.5f, 0.5f);

		int m_tag = 0;
        
        bool m_active = false;

		game_object* m_parent = nullptr;
	};
}
