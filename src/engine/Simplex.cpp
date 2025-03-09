#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "View.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Simplex {

static View view;
static Input input;
static Scene currentScene;

void CreateWindow(std::string title, int width, int height) {
	view.Init(title, width, height);

    // Load Shaders
	ResourceManager::Init();
};

void Quit() {
	view.Quit();
}

void SetScene(Scene scene) {
    currentScene = scene;
};

void Loop() {
	while (!view.ShouldQuit()) {
		view.ClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		currentScene.Update();

		input.PollEvents();
		view.SwapBuffers();
	}
	Quit();
}

} // namespace Simplex
