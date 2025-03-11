#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <vector>
#include "IComponent.hpp"

class Entity {
  public:
	int ID;

	std::vector<IComponent *> Components;

	void AddComponent(IComponent *component);

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

	void UpdateComponents();
};

#endif
