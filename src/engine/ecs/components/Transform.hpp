#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../IComponent.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

struct Transform : public IComponent {
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 Size = glm::vec2(1.0f, 1.0f);
	float Rotation = 0.0f;

	void Update() override {};
};

#endif
