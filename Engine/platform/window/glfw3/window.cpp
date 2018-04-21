#include "common.h"

#include "core/director.h"
#include "core/application.h"

#include "platform/window/window.h"

#include "GLFW3/glfw3.h"

namespace engine
{   
    GLFWwindow* g_window = nullptr;
    bool g_mouse_down = false;
    
	math::vector2d get_mouse_location(GLFWwindow* window)
	{
        auto win_size = application::instance().get_win_size();
        
		double x, y;
		glfwGetCursorPos(window, &x, &y);

        y = win_size.y - y;
        
		return math::vector2d((float)x, (float)y);
	}
    
    bool check_mouse_location(const math::vector2d& mouse)
    {
        auto win_size = application::instance().get_win_size();
        
        return mouse.x >= 0 && mouse.x <= win_size.x && mouse.y >= 0 && mouse.y <= win_size.y;
    }
    
    math::vector2d correct_mouse_location(const math::vector2d& mouse)
    {
        math::vector2d m;
        
        auto win_size = application::instance().get_win_size();
        
        m.x = std::max(0.0f, std::min(mouse.x, win_size.x));
        m.y = std::max(0.0f, std::min(mouse.y, win_size.y));
        
        return m;
    }
	
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
            auto mouse = get_mouse_location(window);
            
            if (action == GLFW_PRESS)
            {
                if (check_mouse_location(mouse))
                {
                    director::instance().handle_mouse_down(mouse);
                    g_mouse_down = true;
                }
            }
            else if (action == GLFW_RELEASE)
            {
                if (g_mouse_down)
                    director::instance().handle_mouse_up(mouse);
                g_mouse_down = false;
            }
		}
	}

	void mouse_move_callback(GLFWwindow* window, double x, double y)
	{
        auto mouse = correct_mouse_location(get_mouse_location(window));
        
        director::instance().handle_mouse_move(mouse);
	}

    void window_close_callback(GLFWwindow* window)
    {
        application::instance().on_terminated();
    }
    
    void window_iconify_callback(GLFWwindow* window, int iconified)
    {
        if (iconified)
        {
            application::instance().on_enter_background();
        }
        else
        {
            application::instance().on_enter_foreground();
        }
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
        
		glfwSetCursorPosCallback(g_window, mouse_move_callback);
		glfwSetMouseButtonCallback(g_window, mouse_button_callback);
        
        glfwSetWindowCloseCallback(g_window, window_close_callback);
        glfwSetWindowIconifyCallback(g_window, window_iconify_callback);

		return true;
	}

	void window::process()
    {
		while (!glfwWindowShouldClose(g_window))
        {           
			director::instance().main_loop();
            
            glfwSwapBuffers(g_window);
            glfwPollEvents();
        }
        
        terminate();
    }
    
    void window::terminate()
    {
        glfwTerminate();
    }
}
