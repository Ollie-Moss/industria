#include "Entity.hpp"
#include "IComponent.hpp"
#include <vector>

void Entity::AddComponent(IComponent *component) {
	component->entity = this;
	Components.push_back(component);
};

template <typename T>
IComponent *Entity::GetComponent() {
	for (int i = 0; i < Components.size(); i++) {
		IComponent *component = Components[i];
		if (dynamic_cast<T*>(component)) {
			return component;
		}
		return nullptr;
	}
};

void Entity::UpdateComponents() {
	for (int i = 0; i < Components.size(); i++) {
		IComponent *component = Components[i];
		component->Update();
	}
};
