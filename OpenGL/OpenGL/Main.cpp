#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <math.h>
// GLFW
#include <GLFW/glfw3.h>


// Function prototypes
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
static void window_callback(GLFWwindow* window, int w, int h);
GLuint VBO, VBO2, VAO, VAO2;
GLuint * pVAO = new GLuint(0);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourcolor; \n"
"void main()\n"
"{\n"
"color = ourcolor;  // vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\n\0";

const GLchar* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.2f, 0.1f, 0.6f, 1.0f);\n"
"}\n\0";
GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f, // Left  
	0.5f, -0.5f, 0.0f, // Right 
	-0.5f,  0.5f, 0.0f,  // Top  

	0.5f, -0.5f, 0.0f, // Left  
	-0.5f, -0.5f, 0.0f, // Right 
	-0.5f,  0.5f, 0.0f  // Top   
};
GLfloat vertices2[] = {
	0.5f, -0.5f, 0.3f, // Left  
	-0.5f, -0.2f, 7.0f, // Right 
	1.0f,  0.3f, 1.0f,  // Top   
	0.5f, -4.0f, 0.1f, // Right 
};
GLuint indices2[] =
{
	0 ,3,1,
	1, 0 ,2,

};
// The MAIN function, from here we start the application and run the game loop
int main()
{
	
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	GLint nrattributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrattributes);
	std::cout << nrattributes;
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	// Check for compile time errors
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	// Check for linking errors
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	// Set up vertex data (and buffer(s)) and attribute pointers


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	GLuint EBO2;
	glGenBuffers(1, &EBO2);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

						  // Game loop
	GLint colorlocation = glGetUniformLocation(shaderProgram, "ourcolor");
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		
	 	glUseProgram(shaderProgram);
		glUniform4f(colorlocation, (std::sin(glfwGetTime()) / 2) + 0.5,
			(std::cos(glfwGetTime()) / 2) + 0.5,
			(std::sin(glfwGetTime()) / 2) + 0.5,
			(std::sin(glfwGetTime()) / 2) + 0.5);
		glBindVertexArray(*pVAO);
		if (pVAO == &VAO)
			glDrawArrays(GL_TRIANGLES, 0, 6);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // this drwas based on indices
			glDrawArrays(GL_TRIANGLES, 0, 9);// it dosent dars the 2 triangels!! we need to call 
											 //glDrawElements. so althout EBO is binded to VAO2 but just callign VAO2 dosnt drwas usisng EBO
		}

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_2)
		pVAO = &VAO2;
	if (key == GLFW_KEY_1)
		pVAO = &VAO;
	if (key == GLFW_KEY_O)
	{// this dosent work!! i cant bind new data to VAO this way !
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f, // Left  
			0.5f, -0.5f, 0.0f, // Right 
			0.0f,  0.5f, 0.0f  // Top   
		};
		GLfloat vertices2[] = {
			0.5f, -0.5f, 0.3f, // Left  
			-0.5f, -0.2f, 0.0f, // Right 
			0.0f,  0.5f, 1.0f  // Top   
		};
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (key == GLFW_KEY_N)
	{
		GLfloat vertices[] = {
			-0.5f, -0.3f, 1.0f, // Left  
			0.5f, -0.2f, 0.1f, // Right 
			0.0f,  0.5f, 0.0f  // Top   
		};
		GLfloat vertices2[] = {
			0.5f, -1.f, 0.3f, // Left  
			-1.0f, 0.2f, 0.0f, // Right 
			0.0f,  0.5f, 1.0f  // Top   
		};
	}
}
void window_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}