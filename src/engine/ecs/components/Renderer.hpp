#ifndef RENDERER_H
#define RENDERER_H

#include "../IComponent.hpp"
#include "Transform.hpp"
#include "../../utils/Model.hpp"
#include "../../ResourceManager.hpp"
#include "../../utils/Shader.hpp"
#include <iostream>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include "../Entity.hpp"
#include "../../Simplex.hpp"

struct Renderer : IComponent {
	Model *model;

	Renderer(Model *model) : model(model) {};
	void Update() override {
		Shader shader = ResourceManager::GetShader("QuadShader");
		shader.use();

		shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		glm::mat4 projection = glm::ortho(0.0f, 19.2f, 0.0f, 10.8f, -100.0f, 100.0f);

		shader.setMat4("projection", projection);

		Transform *transform = entity->GetComponent<Transform>();
		glm::vec3 pos = transform->Position;
		std::vector<float> vertices = {pos.x, pos.y, pos.x, pos.y + 1.0f, pos.x + 1.0f, pos.y, pos.x + 1.0f, pos.y + 1.0f};
		model->bindings["in_vert"]->Fill(vertices);

		model->Render();
	}
};

#endif
