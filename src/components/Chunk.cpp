#include "Chunk.hpp"
#include "ChunkRenderer.hpp"

void Chunk::Generate(int scaleFactor) {
	tiles = MapGenerator::Generate(transform->position.x, transform->position.y, scaleFactor);
	Generated = (scaleFactor == 1);
	renderer->AddChunkToSSBO(*this);
}

void Chunk::Update() {
	for (auto tile : tiles) {
		tile->UpdateComponents();
	}
}
