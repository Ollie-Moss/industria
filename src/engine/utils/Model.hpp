#ifndef MODEL_H
#define MODEL_H

#include "Buffer.hpp"
#include "../ecs/components/Camera.hpp"
#include "../ResourceManager.hpp"
#include "SSBOBuffer.hpp"
#include "Shader.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtx/string_cast.hpp>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include "../Simplex.hpp"

struct Model {
	unsigned int vao;
	std::map<std::string, int> bindingPoints;
	std::map<std::string, Buffer *> bindings;
	size_t SIZE;

	Model() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}
	Model(std::vector<std::string> binds) : Model() {
		for (auto bind : binds) {
			bindingPoints[bind] = (int)bindingPoints.size();
			glEnableVertexAttribArray(bindingPoints[bind]);
		}
	}
	~Model() {
		glDeleteVertexArrays(1, &vao);
	}

	template <typename T>
	void Bind(std::string binding, Buffer *buffer) {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
		glVertexAttribPointer(bindingPoints[binding], sizeof(T) / sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, 0, (void *)0);

		bindings[binding] = buffer;
	}

	void Render(GLenum mode = GL_TRIANGLE_STRIP) {
		glBindVertexArray(vao);
		glDrawArrays(mode, 0, SIZE);
		glBindVertexArray(0);
	}
};

struct Quad : Model {
	Buffer vert, tex;
	Quad() : Model({"in_vert", "in_tex"}),
			 vert({0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}),
			 tex({0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}) {
		Bind<glm::vec2>("in_vert", &vert);
		Bind<glm::vec2>("in_tex", &tex);
		SIZE = 4;
	}
	void Render(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
		std::vector<float> vertices = {position.x, position.y,			//
									   position.x, position.y + size.y, //
									   position.x + size.x, position.y, //
									   position.x + size.x, position.y + size.y};
		vert.Fill(vertices);
		Bind<glm::vec2>("in_vert", &vert);
		Shader shader = ResourceManager::GetShader("QuadShader");
		shader.use();
		glm::mat4 projection = glm::ortho(0.0f, (float)Simplex::view.Width, (float)Simplex::view.Height, 0.0f, -100.0f, 100.0f);

		shader.setVec4("color", color);
		shader.setMat4("projection", projection);
		Model::Render();
	}
};

struct Triangle : Model {
	Buffer vert, tex;
	Triangle() : Model({"in_vert", "in_tex"}),
				 vert({0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f}),
				 tex({0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f}) {
		Bind<glm::vec2>("in_vert", &vert);
		Bind<glm::vec2>("in_tex", &tex);
		SIZE = 3;
	}
};

struct ChunkModel : Model {
	std::unordered_map<std::string, SSBO<unsigned int>> buffers;
	ChunkModel() : Model() {};

	void Fill(std::string texture, std::vector<unsigned int> buf) {
		buffers[texture].Fill(buf);
	}
	void Set(std::string texture, int index, unsigned int value) {
		buffers[texture].Set(index, value);
	}

	void Render() {
		for (auto &pair : buffers) {
			std::string textureName = pair.first;
			SSBO<unsigned int> &ssbo = pair.second;

			Shader shader = ResourceManager::GetShader("SpriteShader");
			shader.use();

			SIZE = ssbo.size / 2 * 6;
			ssbo.Bind();

			glm::mat4 projection = Simplex::view.Camera->GetComponent<Camera>()->CalculateProjection();

			shader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 0.0));
			shader.setMat4("projection", projection);

			glActiveTexture(GL_TEXTURE0);
			ResourceManager::GetTexture(textureName).Bind();
			Model::Render(GL_TRIANGLES);

			glBindTexture(GL_TEXTURE0, 0);
		}
	}
};
#endif
