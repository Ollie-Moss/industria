#ifndef VIEW_H
#define VIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

class View {
  public:
	GLFWwindow *window;
	int Width;
	int Height;
	std::string Title;

	void Init(std::string title, int width, int height);
	bool ShouldQuit();
	void Quit();
	void ClearColor(glm::vec4 color);
	void SwapBuffers();

};

#endif
