#ifndef INPUT_H
#define INPUT_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <map>
#include <vector>

class Input {
  public:
	std::map<int, bool> mouseButtonState;
	std::map<int, bool> keyState;

	std::vector<std::function<void(float)>> scrollCallbacks;

	void Init();

	bool KeyPressed(int button);
	bool MouseButtonPressed(int button);
	bool KeyDown(int button);
	bool MouseButtonDown(int button);

	void ResetMouseButtons();
	void ResetKeys();
	void PollEvents();

	void AddScrollCallback(std::function<void(float)> callback) {
		scrollCallbacks.push_back(callback);
	};

	static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
	static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};
#endif
