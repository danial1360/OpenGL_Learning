#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
void key_callback(GLFWwindow* window, int key, int scancode, int action,	int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose 	property to true,
		// closing the application
	if (key == GLFW_KEY_F )
	{
		//glfwSetWindowShouldClose(window, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}
	else
	{
		 
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

}
void main()
{
	if (glfwInit() == GL_FALSE)
	{
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// important it has to be GLFW_CONTEXT_VERSION_MAJOR not GLFW_VERSION_MAJOR
	//GLFW_VERSION_MAJOR is old so the GLFW_OPENGL_CORE_PROFILE will fail and it cant creat a window 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// GLFW_OPENGL_PROFILE specifies which OpenGL profile to create the context for
	 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow*my_window = glfwCreateWindow(800, 600, "hello word", nullptr, nullptr);
	if (my_window==nullptr)
	{
		return;
	}
	glfwMakeContextCurrent(my_window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return;
	}
	glViewport(0, 0, 800, 600);
	glfwSetKeyCallback(my_window, &key_callback);
	while (!glfwWindowShouldClose(my_window))
	{
		glfwPollEvents();
		//glfwSwapBuffers(my_window);
	}
	glfwTerminate();
}