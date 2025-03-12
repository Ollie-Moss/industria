#ifndef CHUNK_ENTITY_H
#define CHUNK_ENTITY_H

#include "../engine/ecs/Entity.hpp"
#include "ChunkRenderer.hpp"

struct ChunkEntity : Entity {
	ChunkEntity() {
		AddComponent(new ChunkRenderer(new ChunkModel));
		AddComponent(new Transform);
		AddComponent(
			new Chunk(
				GetComponent<ChunkRenderer>(),
				GetComponent<Transform>() //
				));

	};
};

#endif
