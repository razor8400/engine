#pragma once

#include "common.h"

namespace engine
{
	class game_object
	{
	public:
        virtual bool init() { return true; }
        
		virtual void update(float dt);
		virtual void draw();
        virtual void render();
        
        virtual void on_enter();
        virtual void on_exit();

        virtual void add_child(game_object* obj);
		virtual void add_child(game_object* obj, int z_order);
		virtual void remove_child(game_object* obj);
		virtual void remove_from_parent();
    public:
		void set_position(const vector2d& position) { m_position = position; }
		const vector2d& get_position() const { return m_position; }

		void set_rotation(const vector2d& rotation) { m_rotation = rotation; }
		const vector2d& get_rotation() const { return m_rotation; }

		void set_scale(const vector2d& scale) { m_scale = scale; }
		const vector2d& get_scale() const { return m_scale; }

		void set_size(const vector2d& size) { m_size = size; }
		const vector2d& get_size() const { return m_size; }

		void set_anchor(const vector2d& anchor) { m_anchor = anchor; }
		const vector2d& get_anchor() const { return m_anchor; }
        
        void set_z_order(int z_order) { m_z_order = z_order; }
        int get_z_order() const { return m_z_order; }
        
        int get_children_count() const { return (int)m_children.size(); }
	protected:
		std::vector<game_object*> m_children;

		vector2d m_position;
		vector2d m_rotation;
		vector2d m_scale;
		vector2d m_size;
        vector2d m_anchor = vector2d(0.5f, 0.5f);
        
        int m_z_order = 0;
        bool m_active = false;

		game_object* m_parent = nullptr;
	};
}
