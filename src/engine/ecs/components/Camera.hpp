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
#include "iostream"

template <typename T>
struct RectBounds {
	T top;
	T left;
	T bottom;
	T right;

	bool InBounds(T x, T y) {
		return (left <= x && x <= right &&
				bottom <= y && y <= top);
	};
};

struct Camera : public IComponent {
	Transform *transform;

	float zoom = 50.0f;
	float scrollSensitivity = 0.1f;

	glm::vec2 lastMousePos = glm::vec2(0, 0);

	Camera() {};

	RectBounds<float> GetCameraBounds() {
		float orthoWidth = Simplex::view.Width / zoom;
		float orthoHeight = Simplex::view.Height / zoom;

		float cameraLeft = transform->Position.x - orthoWidth / 2.0f;
		float cameraRight = transform->Position.x + orthoWidth / 2.0f;
		float cameraTop = transform->Position.y - orthoHeight / 2.0f;
		float cameraBottom = transform->Position.y + orthoHeight / 2.0f;

		return {cameraTop, cameraRight, cameraBottom, cameraLeft};
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
			// std::cout << zoom << std::endl;
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
