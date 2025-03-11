#include "engine/Simplex.hpp"
#include "engine/ecs/components/Renderer.hpp"
#include "engine/ecs/components/Transform.hpp"
#include "engine/utils/Model.hpp"

int main() {
	Simplex::CreateWindow("Industria", 1280, 720);

	Scene main = Scene();
	main.CreateScene([&]() {
		Entity* tile = new Entity();
		Transform *transform = new Transform();
		transform->Position.x += 5.0f;
		tile->AddComponent(transform);

		tile->AddComponent(new Renderer(new Quad));
		main.entities.push_back(tile);
	});

	Simplex::SetScene(main);

	Simplex::Loop();

	return 0;
}
