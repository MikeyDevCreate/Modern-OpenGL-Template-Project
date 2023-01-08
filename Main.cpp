#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left corner
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right corner
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down corner
	};

	GLuint indices[] =
	{
		0, 3, 5, // lower left trinagle
		3, 2, 4, // lower right triangle
		5, 4, 1 // Upper Triangle
	};

	// Create the window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Tutorial", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Could not create GLFW3 window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Load OpenGL
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	while (!glfwWindowShouldClose(window))
	{
		// clear the screen with a blueish color
		glClearColor(0.4f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean Up to avoid memory leaks
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}