#pragma once

#include "common.h"

namespace engine
{
	class game_object
	{
	public: 
		template<class T>
		static std::shared_ptr<T> create();

		virtual bool init();

		virtual void update(float dt);
		virtual void draw(const math::mat4& world);
        virtual void render(const math::mat4& world);
        
        virtual void on_enter();
        virtual void on_exit();

        virtual void add_child(const game_object_ptr& obj);
		virtual void remove_child(game_object* obj);
		virtual void remove_from_parent();
		
		void mark_dirty() { m_update_transform = true; }

		const math::mat4& transfrom() const { return m_transform; }

		math::mat4 parent_transform() const;
		math::mat4 world_transform() const;
    public:
		void set_position(const math::vector3d& position) { m_position = position; mark_dirty(); }
		const math::vector3d& get_position() const { return m_position; }

		void set_rotation(const math::vector3d& rotation) { m_rotation = rotation; mark_dirty(); }
		const math::vector3d& get_rotation() const { return m_rotation; }

		void set_scale(const math::vector3d& scale) { m_scale = scale; mark_dirty(); }
		const math::vector3d& get_scale() const { return m_scale; }

		void set_size(const math::vector3d& size) { m_size = size; mark_dirty(); }
		const math::vector3d& get_size() const { return m_size; }

		void set_anchor(const math::vector3d& anchor) { m_anchor = anchor; mark_dirty(); }
		const math::vector3d& get_anchor() const { return m_anchor; }

		void set_tag(int tag) { m_tag = tag; }
		int get_tag() const { return m_tag; }
                
        int get_children_count() const { return (int)m_children.size(); }
        
        void set_shader_program(const gl::shader_program_ptr& shader_program) { m_shader_program = shader_program; }
        const gl::shader_program_ptr& get_shader_program() const { return m_shader_program; }
	protected:
		std::vector<game_object_ptr> m_children;

		math::vector3d m_position;
		math::vector3d m_rotation;
		math::vector3d m_scale;
		math::vector3d m_size;
        math::vector3d m_anchor;

		math::mat4 m_transform;

		int m_tag = 0;
        
        bool m_active = false;
		bool m_update_transform = false;

		game_object* m_parent = nullptr;
        gl::shader_program_ptr m_shader_program;
	};

	template<class T>
	inline std::shared_ptr<T> game_object::create()
	{
		auto obj = std::make_shared<T>();

		if (obj->init())
			return obj;

		return nullptr;
	}
}
