#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Input.hpp"
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <vector>

enum LAYOUT_DIRECTION {
	DIRECTION_VERTICAL,
	DIRECTION_HORIZONTAL,
};

enum SIZING_TYPE {
	SIZING_TYPE_FIT,
	SIZING_TYPE_GROW,
	SIZING_TYPE_PERCENT,
	SIZING_TYPE_FIXED,
};

struct SIZING_AXIS {
	std::vector<int> minMax;
	SIZING_TYPE type = SIZING_TYPE_FIT;
};

template <typename... Args>
SIZING_AXIS FIT(Args... args) {
	return {
		.minMax = {args...},
		.type = SIZING_TYPE_FIT,
	};
};
template <typename... Args>
SIZING_AXIS FIXED(Args... args) {
	return {
		.minMax = {args...},
		.type = SIZING_TYPE_FIXED,
	};
};

struct UIElementProperties {
	SIZING_AXIS sizing[2] = {FIT(), FIT()};
	int padding[4] = {0, 0, 0, 0};
    
	glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};

struct UIElement {
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 size = glm::vec2(0, 0);
	glm::vec4 backgroundColor = glm::vec4(0, 0, 0, 1);

	UIElement *parent;
	std::vector<UIElement> children;
};

struct TextNode : UIElement {
	std::string text = "";
	glm::vec4 color = glm::vec4(0, 0, 0, 1);
};

struct ImageNode : UIElement {
	std::string texture = "";
};

class UI {
	UIElement Root;
	UIElement *currentElement = nullptr;

  public:
	UI(UIElement root) : Root(root) {
		currentElement = &Root;
	};

	void OpenElement(UIElement elem) {
		currentElement->children.push_back(elem);
		currentElement = &currentElement->children.back();
	};
	void CloseElement() {
		currentElement = currentElement->parent;
	};

	void Render();
};

UI testUserinterface() {

	UI testUI({.position = glm::vec2(1, 1), .size = glm::vec2(10, 10)});
	testUI.OpenElement(
		{
			.position = glm::vec2(1, 1),
			.size = glm::vec2(10, 10),
		});
	testUI.CloseElement();

	return testUI;
}

#endif
