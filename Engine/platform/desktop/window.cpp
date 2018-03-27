#include "core/director.h"
#include "platform/window.h"
#include "GLFW3/glfw3.h"

namespace engine
{   
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
		return true;
	}

	void window::process()
    {
        glfwMakeContextCurrent(m_window);
        
        while (!glfwWindowShouldClose(m_window))
        {
            /* Render here */
           // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers
            
			director::instance().main_loop();

            /* Swap front and back buffers */
            glfwSwapBuffers(m_window);
            
            /* Poll for and process events */
            glfwPollEvents();
        }
        
        glfwTerminate();
    }
}
