#ifndef MODEL_H
#define MODEL_H

#include "Buffer.hpp"
#include <map>
#include <string>
#include <glm/glm.hpp>

struct Model {
	unsigned int vao;
	std::map<std::string, int> bindingPoints;
	std::map<std::string, Buffer *> bindings;
	int SIZE;

	Model() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}
	Model(std::vector<std::string> binds) : Model() {
		for (auto bind : binds) {
			bindingPoints[bind] = bindingPoints.size();
			glEnableVertexAttribArray(bindingPoints[bind]);
		}
	}
	~Model() {
		glDeleteVertexArrays(1, &vao);
	}

	template <typename T>
	void Bind(std::string binding, Buffer *buffer) {
		glBindVertexArray(vao);
		glBindBuffer(GL_VERTEX_ARRAY, buffer->ID);
		glVertexAttribPointer(bindingPoints[binding], sizeof(T) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(T), (void *)0);
		glBindVertexArray(0);

		bindings[binding] = buffer;
	}

	void Render(GLenum mode = GL_TRIANGLES) {
		glBindVertexArray(vao);
		glDrawArrays(mode, 0, SIZE);
		glBindVertexArray(0);
	}
};

struct Quad : Model {
	Buffer vert, tex;
	Quad() : vert({0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f}),
			 tex({0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f}),
			 Model({"in_vert", "in_tex"}) {
		Bind<glm::vec2>("in_vert", &vert);
		Bind<glm::vec2>("in_tex", &tex);
		SIZE = 6;
	}
};
#endif
