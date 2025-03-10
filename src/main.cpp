#include "engine/Simplex.hpp"
#include "engine/ecs/components/Renderer.hpp"
#include "engine/utils/Model.hpp"

int main() {
	Simplex::CreateWindow("Industria", 1280, 720);

	Scene main = Scene();
	main.CreateScene([&]() {
		Entity tile = Entity();
		tile.AddComponent(new Renderer(new Quad));
		main.entities.push_back(tile);
	});

	Simplex::SetScene(main);

	Simplex::Loop();

	return 0;
}
