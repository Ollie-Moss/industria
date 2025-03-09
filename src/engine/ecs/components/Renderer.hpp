#ifndef RENDERER_H
#define RENDERER_H

#include "../IComponent.hpp"
#include "../../utils/Model.hpp"
#include "../../ResourceManager.hpp"
#include "../../utils/Shader.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>

struct Renderer : IComponent {
	Quad model = Quad();

	Renderer() {};
	void Update() override {
		Shader shader = ResourceManager::GetShader("QuadShader");
		shader.use();

		shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		glm::mat4 projection = glm::ortho(0.0f, 19.2f, 0.0f, 10.8f, -100.0f, 100.0f);

		shader.setMat4("projection", projection);

		model.Render();
	}
};

#endif
