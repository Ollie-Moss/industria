#ifndef CAMERA_H
#define CAMERA_H

#include "../IComponent.hpp"
#include "Transform.hpp"
#include "../../Simplex.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../../../components/MapGenerator.hpp"

#define CHUNK_PADDING 2 

struct Camera : public IComponent {
	Transform *transform;

	float zoom = 50.0f;
	float scrollSensitivity = 0.1f;

	glm::vec2 lastMousePos = glm::vec2(0, 0);

	Camera() {};

	std::pair<glm::ivec2, glm::ivec2> GetChunkPositionsInView() {
		// Calculate the orthographic viewport dimensions
		float orthoWidth = Simplex::view.Width / zoom;
		float orthoHeight = Simplex::view.Height / zoom;

		// Calculate the world boundaries of the camera's viewport based on the zoomed ortho size
		float cameraLeft = transform->Position.x - orthoWidth / 2.0f;
		float cameraRight = transform->Position.x + orthoWidth / 2.0f;
		float cameraTop = transform->Position.y - orthoHeight / 2.0f;
		float cameraBottom = transform->Position.y + orthoHeight / 2.0f;

		// Convert world coordinates to chunk coordinates (taking zoom into account)
		int chunkXStart = static_cast<int>(std::floor(cameraLeft / CHUNK_SIZE));
		int chunkXEnd = static_cast<int>(std::floor(cameraRight / CHUNK_SIZE));
		int chunkYStart = static_cast<int>(std::floor(cameraTop / CHUNK_SIZE));
		int chunkYEnd = static_cast<int>(std::floor(cameraBottom / CHUNK_SIZE));

		glm::ivec2 chunkStart = glm::ivec2(chunkXStart, chunkYStart) - CHUNK_PADDING;
		glm::ivec2 chunkEnd = glm::ivec2(chunkXEnd, chunkYEnd) + CHUNK_PADDING;

		return std::pair<glm::ivec2, glm::ivec2>(chunkStart, chunkEnd);
	}

	glm::mat4 CalculateProjection() {
		float orthoWidth = Simplex::view.Width / zoom;
		float orthoHeight = Simplex::view.Height / zoom;
		glm::mat4 projection = glm::ortho(
			transform->Position.x - orthoWidth / 2, transform->Position.x + orthoWidth / 2,
			transform->Position.y - orthoHeight / 2,
			transform->Position.y + orthoHeight / 2, -100.0f, 100.0f);
		return projection;
	}

	void Start() override {
		transform = entity->GetComponent<Transform>();
		Simplex::input.AddScrollCallback([&](float yOffset) -> void {
			zoom += ((float)yOffset * scrollSensitivity * zoom) / 10.0f;
		});
	}
	void Update() override {
		glm::vec2 mousePos = Simplex::view.GetMousePosition();

		if (Simplex::input.MouseButtonDown(GLFW_MOUSE_BUTTON_3)) {
			glm::vec2 dragOffset = lastMousePos - mousePos;
			transform->Position += glm::vec3(dragOffset / zoom, 0.0f);
		}
		lastMousePos = mousePos;
	};
};

#endif
