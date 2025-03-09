#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "Input.hpp"
#include "Scene.hpp"
#include "View.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Simplex {

static View view;
static Input input;
static Scene currentScene;

void CreateWindow(std::string title, int width, int height);

void Quit();

void Loop();

void SetScene(Scene scene);

} // namespace Simplex

#endif
