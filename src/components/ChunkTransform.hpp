#ifndef CHUNK_TRANSFORM_H 
#define CHUNK_TRANSFORM_H 

#include "../engine/ecs/IComponent.hpp"
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int3.hpp>

struct ChunkTransform : IComponent {
	glm::ivec2 position = glm::ivec2(0, 0);
};

#endif
