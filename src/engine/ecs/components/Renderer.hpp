#ifndef RENDERER_H
#define RENDERER_H

#include "../IComponent.hpp"
#include "../../utils/Model.hpp"

struct Renderer : IComponent {
	Quad model;
	Renderer(Quad quad) : model(quad) {};
	void Update() override {
		model.Render();
	}
};

#endif
