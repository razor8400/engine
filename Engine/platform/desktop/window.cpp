#include "core/director.h"
#include "platform/window.h"

#include "GLEW/glew.h"
#include "GLFW3/glfw3.h"

namespace engine
{   
	vector2d get_mouse_location(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return vector2d(x, y);
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
		director::instance().handle_mouse_move(vector2d(x, y));
	}

	window::window()
	{

	}

	bool window::create(const char* display_name, int width, int height)
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, display_name, NULL, NULL);
		
		if (!m_window)
		{
			glfwTerminate();
			return false;

		}

		glfwSetCursorPosCallback(m_window, mouse_move_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);

		return true;
	}

	void window::process()
    {
        glfwMakeContextCurrent(m_window);
        
        while (!glfwWindowShouldClose(m_window))
        {
            /* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers
            
			director::instance().main_loop();

            /* Swap front and back buffers */
            glfwSwapBuffers(m_window);
            
            /* Poll for and process events */
            glfwPollEvents();
        }
        
        glfwTerminate();
    }
}
