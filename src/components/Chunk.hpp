#ifndef CHUNK_H
#define CHUNK_H

#include "../engine/ecs/IComponent.hpp"
#include "../engine/ecs/components/Transform.hpp"
#include "../entities/TileEntity.hpp"
#include "ChunkTransform.hpp"
#include "MapGenerator.hpp"

struct ChunkRenderer;

struct Chunk : IComponent {
	std::vector<TileEntity *> tiles;
	ChunkTransform *transform;
	ChunkRenderer *renderer;
	bool Generated = false;

	Chunk(ChunkRenderer *renderer, ChunkTransform *transform) : renderer(renderer),
																transform(transform) {};

	void Generate();

	void Update() override;
};

#endif
