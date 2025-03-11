#include "Entity.hpp"
#include "IComponent.hpp"
#include <vector>

void Entity::AddComponent(IComponent *component) {
	component->entity = this;
	Components.push_back(component);
};

void Entity::StartComponents() {
	for (size_t i = 0; i < Components.size(); i++) {
		IComponent *component = Components[i];
		component->Start();
	}
};

void Entity::UpdateComponents() {
	for (size_t i = 0; i < Components.size(); i++) {
		IComponent *component = Components[i];
		component->Update();
	}
};
