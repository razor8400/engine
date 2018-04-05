#include "common.h"
#include "core/director.h"
#include "platform/window/window.h"

#include "GLFW3/glfw3.h"

namespace engine
{   
    GLFWwindow* g_window = nullptr;
    
	math::vector2d get_mouse_location(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return math::vector2d((float)x, (float)y);
	}
	
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS)
			{
				director::instance().handle_mouse_down(get_mouse_location(window));
			}
			else if (action == GLFW_RELEASE)
			{
				director::instance().handle_mouse_up(get_mouse_location(window));
			}
		}
	}

	void mouse_move_callback(GLFWwindow* window, double x, double y)
	{
		director::instance().handle_mouse_move(math::vector2d((float)x, (float)y));
	}

	window::window()
	{

	}

	bool window::create(const char* display_name, int width, int height)
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		g_window = glfwCreateWindow(width, height, display_name, NULL, NULL);
		m_size.x = (float)width;
		m_size.y = (float)height;
		
		if (!g_window)
		{
			glfwTerminate();
			return false;
		}
        
        glfwMakeContextCurrent(g_window);

        if (!gl::init_gl())
            return false;

		gl::compile_shaders();
        
		glfwSetCursorPosCallback(g_window, mouse_move_callback);
		glfwSetMouseButtonCallback(g_window, mouse_button_callback);

		return true;
	}

	void window::process()
    {
		auto vbo = gl::generate_vbo();

		while (!glfwWindowShouldClose(g_window))
        {           
			director::instance().main_loop();
            
            glfwSwapBuffers(g_window);
            glfwPollEvents();
        }
        
		gl::clear_vbo(vbo);

        glfwTerminate();
    }
}
