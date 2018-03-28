#pragma once

#include "common.h"

namespace engine
{
	class game_object
	{
	public:
		virtual void update(float dt);
		virtual void draw();

		void add_child(game_object* obj);
		void remove_child(game_object* obj);
		void remove_from_parent();

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
	private:
		std::vector<game_object*> m_children;

		vector2d m_position;
		vector2d m_rotation;
		vector2d m_scale;
		vector2d m_size;
		vector2d m_anchor;

		game_object* m_parent = nullptr;
	};
}