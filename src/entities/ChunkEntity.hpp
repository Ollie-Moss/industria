#ifndef CHUNK_ENTITY_H
#define CHUNK_ENTITY_H

#include "../engine/ecs/Entity.hpp"
#include "../components/ChunkRenderer.hpp"
#include <glm/ext/vector_int2.hpp>

struct ChunkEntity : Entity {

	ChunkEntity(glm::ivec2 position) {
		AddComponent(new ChunkRenderer(new ChunkModel));
		AddComponent(new ChunkTransform);
		AddComponent(
			new Chunk(
				GetComponent<ChunkRenderer>(),
				GetComponent<ChunkTransform>() //
				));

		GetComponent<ChunkTransform>()->position = position;

	};
};

#endif
