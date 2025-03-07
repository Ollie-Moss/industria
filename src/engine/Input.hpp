#ifndef INPUT_H
#define INPUT_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <map>

class Input {
  public:
	std::map<int, bool> mouseButtonState;
	std::map<int, bool> keyState;

	bool KeyPressed(int button);
	bool MouseButtonPress(int button);
	bool KeyDown(int button);
	bool MouseButtonDown(int button);

	void PollEvents() { glfwPollEvents(); };
};

#endif
