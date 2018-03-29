#include "core/director.h"
#include "platform/window.h"

#include "gl/gl.h"
#include "GLFW3/glfw3.h"

namespace engine
{
    static const char* frag_shader =   "#version 330 core\
                                        out vec3 color;\
                                        void main()\
                                        {\
                                            color = vec3(1, 1, 1);\
                                        }";
    
    static const char* vert_shader =   "#version 330 core\
                                        layout(location = 0) in vec3 vertexPosition_modelspace;\
                                        void main()\
                                        {\
                                            gl_Position.xyz = vertexPosition_modelspace;\
                                            gl_Position.w = 1.0;\
                                        }";
    
    GLFWwindow* g_window = nullptr;
    
	math::vector2d get_mouse_location(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return math::vector2d(x, y);
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
		director::instance().handle_mouse_move(math::vector2d(x, y));
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
		m_size.x = width;
		m_size.y = height;
		
		if (!g_window)
		{
			glfwTerminate();
			return false;
		}
        
        glfwMakeContextCurrent(g_window);

        if (!gl::init_gl())
            return false;
        
		glfwSetCursorPosCallback(g_window, mouse_move_callback);
		glfwSetMouseButtonCallback(g_window, mouse_button_callback);

		return true;
	}

	void window::process()
    {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
        GLuint program = gl::create_gl_program(vert_shader, frag_shader);
        
		while (!glfwWindowShouldClose(g_window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(program);
            
            static const GLfloat g_vertex_buffer_data[] =
            {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
              //  0.0f,  1.0f, 0.0f,
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
                                  2,                  // Размер
                                  GL_FLOAT,           // Тип
                                  GL_FALSE,           // Указывает, что значения не нормализованы
                                  0,                  // Шаг
                                  NULL            // Смещение массива в буфере
                                  );
            
            // Вывести треугольник!
            glDrawArrays(GL_TRIANGLES, 0, 2); // Начиная с вершины 0, всего 3 вершины -> один треугольник
            
            glDisableVertexAttribArray(0);
            
            director::instance().main_loop();
            
            glfwSwapBuffers(g_window);
            glfwPollEvents();
        }
        
        glfwTerminate();
    }
}
