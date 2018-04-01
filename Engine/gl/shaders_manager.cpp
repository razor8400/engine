#include "gl.h"
#include "shaders.h"
#include "shaders_manager.h"

namespace engine
{
	namespace gl
	{
		namespace default_shaders
		{
			static const char* shader_color = "#version 330 core\n\
												out vec3 color;\
												void main()\
												{\
													color = vec3(1, 1, 1);\
												}";

			static const char* shader_position = "#version 330 core\n\
												layout(location = 0) in vec3 vertexPosition_modelspace;\
												uniform mat4 mvp;\
												void main()\
												{\
													gl_Position = mvp * vec4(vertexPosition_modelspace,1);\
												}";
		}
		
		shaders_manager& shaders_manager::instance()
		{
			static shaders_manager instance;

			return instance;
		}

		template<class T>
		shader_program_ptr shaders_manager::create_gl_program(const char* vert, const char* frag)
		{
			auto program = gl::create_gl_program(vert, frag);

			return std::make_shared<T>(program);
		}

		shaders_manager::shaders_manager()
		{

		}

		void shaders_manager::compile_default_shaders()
		{
			auto position_color = create_gl_program<shader_position_color>(default_shaders::shader_position, default_shaders::shader_color);

			add_to_cache(position_color, shaders::k_shader_position_color);
		}

		void shaders_manager::add_to_cache(const shader_program_ptr& program, const std::string& key)
		{
			m_cache[key] = program;
		}

		const shader_program_ptr& shaders_manager::get_program(const std::string& key) const
		{
			auto it = m_cache.find(key);

			if (it != m_cache.end())
				return it->second;

			static shader_program_ptr null_program;

			return null_program;
		}
	}
}