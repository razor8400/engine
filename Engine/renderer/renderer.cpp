#include "renderer.h"

#include "core/application.h"
#include "core/scene.h"

#include "gl/gl.h"
#include "gl/shaders.h"
#include "gl/shaders_manager.h"

namespace engine
{
	void renderer::set_projection_mode(projection_mode mode)
	{
		m_projection_mode = mode;
		update_world();
	}

	void renderer::set_near_plane(float near_plane)
	{
		m_near_plane = near_plane;
		update_world();
	}

	void renderer::set_far_plane(float far_plane)
	{
		m_far_plane = far_plane;
		update_world();
	}

	void renderer::set_field_of_view(float field_of_view)
	{
		m_field_of_view = field_of_view;
		update_world();
	}

	void renderer::set_camera_position(const math::vector3d& position)
	{
		m_camera_position = math::mat4::look_at(position, math::vector3d::zero, math::vector3d::up);
	}

	void renderer::draw_scene(const scene_ptr& scene)
	{
		if (scene)
		{
			gl::clear();

			auto transform = m_world * m_camera_position;

			scene->draw(transform);
		}
	}

	void renderer::update_world()
	{
		auto win_size = application::instance().get_win_size();

		if (m_projection_mode == perspective)
		{
			m_world = math::mat4::perspective(m_field_of_view, win_size.x / win_size.y, m_near_plane, m_far_plane);
		}
		else if (m_projection_mode == ortographic)
		{
			m_world = math::mat4::ortographic(win_size.x, win_size.y, m_near_plane, m_far_plane);
		}
	}
}
