#pragma once

#include "core/game_object.h"

namespace engine
{   
	struct quad
	{
		std::vector<math::vector2d> vertices;
		std::vector<math::vector2d> uv;
		std::vector<math::vector4d> colors;
	};

    class sprite : public game_object
    {
        DECLARE_CLASS;
    public:
        bool init() override;
        bool init(const std::string& file_name);
		bool init(const texture2d_ptr& texture);
        bool init(const texture2d_ptr& texture, const math::rect& rect);
		bool init(const std::string& atlas_name, const std::string& file_name);

		void draw(const math::mat4& t) override;
        void render(const math::mat4& t) override;

		void clear_texture();
        void set_texture(const std::string& file_name);
        void set_texture(const texture2d_ptr& texture);
        void set_texture(const texture2d_ptr& texture, const math::rect& rect);

        void set_color(const math::vector3d& color) { m_color = color; }
        const math::vector3d& get_color() const { return m_color; }

		math::vector4d get_color_rgba() const { return math::vector4d(m_color.x, m_color.y, m_color.z, get_alpha()); }
		
        void set_alpha(float alpha);
        float get_alpha() const;
        const texture2d_ptr& get_texture() const { return m_texture; }

		void set_blend_func(const gl::blend_func& blend_func) { m_blend_func = blend_func; }
		const gl::blend_func& get_blend_func() const { return m_blend_func; }

		const math::rect& get_texture_rect() const { return m_texture_rect; }
		void set_texture_rect(const math::rect& texture_rect) { m_texture_rect = texture_rect; }

		quad update_quad() const;
    protected:
        texture2d_ptr m_texture;
		math::rect m_texture_rect;

		bool m_rotated = false;

		quad m_quad;

        math::vector3d m_color = math::vector3d::one;
		gl::blend_func m_blend_func = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
    };
}
