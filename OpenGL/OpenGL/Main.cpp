#define GLEW_STATIC
#include <GL\glew.h>
#include<GLFW\glfw3.h>
#include <iostream>
const char * m_vertexshader[] = { "#version 330 core\n \
layout (location =0) in vect3 position;\n \
void main()\n \
{\n \
	gl_Position = vec4(position.x,position.y,position.z,1.0);\n \
}" };
const char* m_fragmentshader[] = { "#version 330 core\
out vec4 color;\
void main()\
{\
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
}" };
GLfloat vitexdata[] = { -0.5f, -0.5f, 0.0f,
                         0.5f, -0.5f, 0.0f,
	                     0.0f, 0.5f, 0.0f };
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
		//
		GLuint m_vbo;
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vitexdata), vitexdata, GL_STATIC_DRAW);
		// compile the shader
		GLuint m_vshader=glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vshader, 1,  m_vertexshader, nullptr);
		glCompileShader(m_vshader);
		GLint res;
		GLchar loginfo[512];
		glGetShaderiv(m_vshader, GL_COMPILE_STATUS, &res);
		if (!res)
		{
			glGetShaderInfoLog(m_vshader, 512, NULL, loginfo);
			std::clog << loginfo << std::endl;
		}

		
		GLuint m_fshader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fshader, 1, m_fragmentshader, nullptr);
		glCompileShader(m_fshader);
		glGetShaderiv(m_fshader, GL_COMPILE_STATUS, &res);
		if (!res)
		{
			glGetShaderInfoLog(m_fshader, 512, NULL, loginfo);
			std::clog << loginfo << std::endl;
		}
		GLuint finalshaderprogram=glCreateProgram();
		glAttachShader(finalshaderprogram, m_vshader);
		glAttachShader(finalshaderprogram, m_fshader);
		glLinkProgram(finalshaderprogram);
		glGetProgramiv(finalshaderprogram, GL_LINK_STATUS, &res);
		if (!res)
		{
			glGetProgramInfoLog(finalshaderprogram,512,NULL, loginfo);
			std::clog << loginfo << std::endl;
		}

		glUseProgram(finalshaderprogram);
		glDeleteShader(m_vbo);
		glDeleteShader(m_fshader);
		//
		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
		glfwTerminate();
}