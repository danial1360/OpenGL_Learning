#define GLEW_STATIC
#include <GL\glew.h>
#include<GLFW\glfw3.h>
#include <iostream>
void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow * m_window = glfwCreateWindow(800, 600, "non", nullptr, nullptr);
		if (m_window == nullptr)
		{
			return ;
		}
		glfwMakeContextCurrent(m_window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			return;
		}
		glViewport(0, 0, 200, 200);
		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
		glfwTerminate();
}