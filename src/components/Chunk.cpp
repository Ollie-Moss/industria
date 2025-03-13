#include "Chunk.hpp"
#include "ChunkRenderer.hpp"

void Chunk::Generate() {
	tiles = MapGenerator::Generate(transform->position.x, transform->position.y);
	Generated = true;
	renderer->AddChunkToSSBO(*this);
}

void Chunk::Update() {
	for (auto tile : tiles) {
		tile->UpdateComponents();
	}
}
