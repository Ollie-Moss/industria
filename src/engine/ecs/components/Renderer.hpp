#ifndef RENDERER_H
#define RENDERER_H

#include "../IComponent.hpp"
#include "../../utils/Model.hpp"
#include "../../ResourceManager.hpp"
#include "../../utils/Shader.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include "../../utils/SSBOBuffer.hpp"
#include "../../Simplex.hpp"
#include "Camera.hpp"
#include "../../Userinterface.hpp"

struct bigModel : Model {
	SSBO<unsigned int> ssbo;
	bigModel() : Model(), ssbo(SSBO<unsigned int>()) {
		ssbo.Bind();
	};
	void fillSSBO(std::vector<unsigned int> buf) {
		ssbo.Fill(buf);
		SIZE = ssbo.size / 2 * 6;
	}
};

struct Renderer : IComponent {
	bigModel model = bigModel();

	Renderer() {};
	void Update() override {
		Shader shader = ResourceManager::GetShader("SpriteShader");
		shader.use();

		glm::mat4 projection = glm::mat4(1.0f);
		if (Simplex::view.Camera != nullptr) {
			projection = Simplex::view.Camera->GetComponent<Camera>()->CalculateProjection();
		}

		shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		shader.setMat4("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		ResourceManager::GetTexture("GRASS_TILE_1").Bind();
		model.Render(GL_TRIANGLES);
		glBindTexture(GL_TEXTURE0, 0);

	}
};

#endif
