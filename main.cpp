#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"

#include "windows.h"
double zoom = 450.0;
int iterations = 50;
int width = 1600;
int height = 900;
double offset[2] = { -(width/2.0)/zoom, -(height/2.0)/zoom };
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
	offset[0] -= ((width  - ::width)  / 2.0) / zoom;
	offset[1] -= ((height - ::height) / 2.0) / zoom;
	::width = width;
	::height = height;
} 
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		offset[0] -= (width/2.0f-xpos)/zoom;
		offset[1] -= (ypos - height / 2.0f)/zoom;
	}
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		double change = 1.01;
		zoom *= change;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		offset[0] += (xpos)/zoom * (change - 1.0);
		offset[1] += (height-ypos)/zoom * (change - 1.0);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		double change = 1.01;
		zoom /= change;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		offset[0] -= (xpos - (xpos / change))/zoom;
		offset[1] -= (height - ypos - ((height -ypos) / change))/zoom;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		iterations += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		iterations -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		offset[1] += 20.0 / zoom;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		offset[1] -= 20.0 / zoom;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		offset[0] -= 20.0 / zoom;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		offset[0] += 20.0/zoom;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		zoom = 450.0;
		iterations = 50;
		offset[0] = -width / 2.0 / zoom;
		offset[1] = -height / 2.0 / zoom;
	}
}
int main()
{
	float triangle4[] = { -1.0f, -1.0f,  0.0f,
						  -1.0f,  1.0f,  0.0f,
						   1.0f,  1.0f,  0.0f,
						   1.0f, -1.0f,  0.0f };
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFWwindow* window = glfwCreateWindow(width, height, "Small window", glfwGetPrimaryMonitor(), NULL);
	GLFWwindow* window = glfwCreateWindow(width, height, "Small window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), triangle4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Shader shader("Shaders/vertex.vert", "Shaders/fragment.frag");
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.0f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO);
		shader.use();
		shader.setUniform("iterations", iterations);
		shader.setUniform("offset", offset[0], offset[1]);
		shader.setUniform("zoom", zoom);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
		Sleep(2);
	}
	glfwTerminate();
	return 0;
}