#include "engine/Simplex.hpp"
#include "engine/ecs/components/Renderer.hpp"

int main() {
	Scene main = Scene();
	main.CreateScene([&]() {
		Entity tile = Entity();
		tile.AddComponent(new Renderer(Quad()));
		main.entities.push_back(tile);
	});

	Simplex::CreateWindow("Industria", 1280, 720);
	Simplex::Loop();

	return 0;
}
