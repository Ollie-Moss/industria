#include "Scene.hpp"

void Scene::Update() {
	for (auto *entity : entities) {
		entity->UpdateComponents();
	}
}

