#include "Simplex.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "View.hpp"
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Simplex {

View view;
Input input;
Scene currentScene;
bool firstLoop = true;

void CreateWindow(std::string title, int width, int height) {
	view.Init(title, width, height);

	input.Init();

	// Load Shaders
	ResourceManager::Init();
};

void Quit() {
	view.Quit();
}

void SetScene(Scene scene) {
	currentScene = scene;
	view.Camera = scene.GetCamera();
};

void Loop() {
	if (firstLoop) {
		currentScene.Start();
		firstLoop = false;
	}
	while (!view.ShouldQuit()) {
		view.ClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		currentScene.Update();

		input.PollEvents();
		view.SwapBuffers();
	}
	Quit();
}

} // namespace Simplex
