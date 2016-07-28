#define GLEW_STATIC
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;
void main()
{
	if (!glfwInit())
	{
		cout << "error initializing GLFW\n";
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

}
 