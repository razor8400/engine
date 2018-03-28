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
		m_size.m_x = width;
		m_size.m_y = height;
		
		if (!m_window)
		{
			glfwTerminate();
			return false;
		}
        
        //glewExperimental = true;
        if (glewInit() != GLEW_OK)
            return false;
        
		glfwSetCursorPosCallback(m_window, mouse_move_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);

		return true;
	}

	void window::process()
    {
        glfwMakeContextCurrent(m_window);

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
		while (!glfwWindowShouldClose(m_window))
        {
            static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
            };
            
            // Это будет идентификатором нашего буфера вершин
            GLuint vertexbuffer;
            
            // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
            glGenBuffers(1, &vertexbuffer);
            
            // Сделаем только что созданный буфер текущим
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            
            // Передадим информацию о вершинах в OpenGL
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                                  0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
                                  3,                  // Размер
                                  GL_FLOAT,           // Тип
                                  GL_FALSE,           // Указывает, что значения не нормализованы
                                  0,                  // Шаг
                                  (void*)0            // Смещение массива в буфере
                                  );
            
            // Вывести треугольник!
            glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник
            
            glDisableVertexAttribArray(0);
            
            director::instance().main_loop();
            
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
        
        glfwTerminate();
    }
}
