#include "pch.hpp"
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

static const float vertices[] = {

	// Vertices		// Color
	 0.5f,  0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,	1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,	0.0f, 1.0f, 1.0f,
};

static const GLuint indices[] = {

	0, 1, 3,
	1, 2, 3
};

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	GLFWwindow *window = glfwCreateWindow(800, 600, "GL Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	glViewport(0, 0, 800, 600);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
	
	Shader shader("../02_hello_triangle/shaders/vertex.vert", "../02_hello_triangle/shaders/fragment.frag", "../02_hello_triangle/shaders/geometry.geom");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Indices Data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 0));
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 2));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		shader.setValue("ourColor", 0.0f, 1.0f, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
		glBindVertexArray(0);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	UNUSED(window);
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
