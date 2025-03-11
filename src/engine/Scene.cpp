#include "Scene.hpp"
#include "ecs/Entity.hpp"
#include "ecs/components/Camera.hpp"

void Scene::Start() {
	for (auto *entity : entities) {
		entity->StartComponents();
	}
}
void Scene::Update() {
	for (auto *entity : entities) {
		entity->UpdateComponents();
	}
}

Entity *Scene::GetCamera() {
	for (size_t i = 0; i < entities.size(); i++) {
		Entity *entity = entities[i];

		if (entity->GetComponent<Camera>() != nullptr) {
			return entity;
		}
	}
	return nullptr;
};
