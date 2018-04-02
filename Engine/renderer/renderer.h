#pragma once

#include "common.h"

namespace engine
{
	class renderer
	{
	public:
		void set_projection_mode(projection_mode mode);

		void set_near_plane(float near_plane);
		void set_far_plane(float far_plane);
		void set_field_of_view(float field_of_view);

		void set_camera_position(const math::vector3d& position);
		void draw_scene(const scene_ptr& scene);
	private:
		void update_world();
	private:
		float m_near_plane = 0;
		float m_far_plane = 0;
		float m_field_of_view = 0;

		projection_mode m_projection_mode;

		math::mat4 m_world;
		math::mat4 m_camera_position;
	};
}