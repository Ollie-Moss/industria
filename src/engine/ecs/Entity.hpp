#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <vector>
#include "IComponent.hpp"

#define ENTITY(name, ...) \
    Entity* name = new Entity; \
    name->AddComponents({__VA_ARGS__}); \
    entities.push_back(name);

class Entity {
  public:
	int ID;

	std::vector<IComponent *> Components;

	void AddComponent(IComponent *component);
	void AddComponents(std::initializer_list<IComponent *> components) {
		for (auto *component : components) {
			AddComponent(component);
		}
	};

	template <typename T>
	T *GetComponent() {
		for (size_t i = 0; i < Components.size(); i++) {
			IComponent *component = Components[i];

			if (T *casted = dynamic_cast<T *>(component)) {
				return casted;
			}
		}
		return nullptr;
	};

	void StartComponents();
	void UpdateComponents();
};

#endif
