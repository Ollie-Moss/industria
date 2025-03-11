#include "Input.hpp"
#include "Simplex.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
	Simplex::input.mouseButtonState[button] = action;
}
void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Simplex::input.keyState[key] = action;
}

void Input::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	for (auto &callback : Simplex::input.scrollCallbacks) {
		callback(yoffset);
	}
}

void Input::Init() {
	glfwSetMouseButtonCallback(Simplex::view.window, Input::MouseButtonCallback);
	glfwSetKeyCallback(Simplex::view.window, Input::KeyCallback);
	glfwSetScrollCallback(Simplex::view.window, Input::ScrollCallback);
}

bool Input::KeyDown(int key) {
	if (Simplex::view.window == nullptr) {
		return false;
	}

	return glfwGetKey(Simplex::view.window, key) == GLFW_PRESS;
}

bool Input::MouseButtonDown(int button) {
	if (Simplex::view.window == nullptr) {
		return false;
	}

	return glfwGetMouseButton(Simplex::view.window, button) == GLFW_PRESS;
}

bool Input::MouseButtonPressed(int button) {
	if (Simplex::view.window == nullptr) {
		return false;
	}

	return mouseButtonState[button];
}
bool Input::KeyPressed(int button) {
	if (Simplex::view.window == nullptr) {
		return false;
	}

	return keyState[button];
}

void Input::PollEvents() {
	ResetMouseButtons();
	ResetKeys();
	glfwPollEvents();
}

void Input::ResetMouseButtons() {
	for (auto &button : mouseButtonState) {
		button.second = false;
	}
}
void Input::ResetKeys() {
	for (auto &key : keyState) {
		key.second = false;
	}
}
