#include "View.hpp"
#include "Simplex.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void View::Init(std::string title, int width, int height) {
	Width = width;
	Height = height;
	Title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, Width, Height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetFramebufferSizeCallback(window, View::FramebufferSizeCallback);
}

void View::FramebufferSizeCallback(GLFWwindow *window, int newWidth, int newHeight) {
    Simplex::view.Width = newWidth;
    Simplex::view.Height = newHeight;
	glViewport(0, 0, Simplex::view.Width, Simplex::view.Height);
}

void View::ClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void View::SwapBuffers() {
	glfwSwapBuffers(window);
}

bool View::ShouldQuit() {
	return glfwWindowShouldClose(window);
}

void View::Quit() {
	glfwTerminate();
}

glm::vec2 View::GetMousePosition() {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec2 mousePos = glm::vec2((float)mouseX, Height - (float)mouseY);
	return mousePos;
}
