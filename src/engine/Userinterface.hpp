#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Input.hpp"
#include <cstdint>
#include "utils/Model.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtx/string_cast.hpp>
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

struct MinMax {
	int min = 0;
	int max = 0;
};

struct SIZING_AXIS {
	MinMax minMax;
	SIZING_TYPE type = SIZING_TYPE_FIT;
};

#define MIN(value) .min = value
#define MAX(value) .max = value

#define FIT(...) \
	SIZING_AXIS { .minMax = {__VA_ARGS__}, .type = SIZING_TYPE_FIT, }
#define FIXED(fixedSize) \
	SIZING_AXIS { .minMax = {fixedSize, fixedSize}, .type = SIZING_TYPE_FIXED, }

enum ELEMENT_TYPE {
	ELEMENT_RECTANGLE,
	ELEMENT_IMAGE,
	ELEMENT_TEXT
};

struct Padding {
	float top = 0.0f;
	float right = 0.0f;
	float bottom = 0.0f;
	float left = 0.0f;
};

struct SIZING {
	SIZING_AXIS xAxis = {};
	SIZING_AXIS yAxis = {};
};

struct UIElementProperties {
	ELEMENT_TYPE type = ELEMENT_RECTANGLE;
	LAYOUT_DIRECTION direction = DIRECTION_HORIZONTAL;
	SIZING sizing = {FIT(), FIT()};
	Padding padding = {0, 0, 0, 0};
	float childGap = 0;
	glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	std::string text = "";
	std::string texture = "";
};

struct UIElement {
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 size = glm::vec2(0, 0);
	UIElementProperties properties = {};

	UIElement *parent;
	std::vector<UIElement> children;
};

class UI {
	UIElement Root = {};
	UIElement *currentElement = &Root;

  public:
	UI() {}

	void OpenElement(UIElementProperties properties) {
		UIElement elem = {
			.properties = properties,
		};

		currentElement->children.push_back(elem);
		currentElement->children.back().parent = currentElement;
		currentElement = &currentElement->children.back();
	};
	void CloseElement() {

		if (currentElement->properties.sizing.xAxis.type == SIZING_TYPE_FIXED) {
			currentElement->size.x = currentElement->properties.sizing.xAxis.minMax.max;
		}
		if (currentElement->properties.sizing.yAxis.type == SIZING_TYPE_FIXED) {
			currentElement->size.y = currentElement->properties.sizing.yAxis.minMax.max;
		}
		currentElement = currentElement->parent;
	};

	void CalculateFitSizingWidths() {}
	void CalculateFitSizingHeights() {}

	void CalculateGrowAndShrinkSizingWidths() {}
	void CalculateGrowAndShrinkSizingHeights() {}

	void WrapText() {}

	void CalculatePositions() {}

	void UpdateLayout() {
		CalculateFitSizingWidths();
		CalculateGrowAndShrinkSizingWidths();
		WrapText();

		CalculateFitSizingHeights();
		CalculateGrowAndShrinkSizingHeights();

		CalculatePositions();
	}

	void RenderElementChildren(UIElement elem) {
		if (elem.children.empty())
			return;

		for (auto child : elem.children) {
			glm::vec2 childPosition = elem.position + child.position;
			childPosition.x += elem.properties.padding.left;
			childPosition.y += elem.properties.padding.top;

			Quad quad = Quad();
			quad.Render(childPosition, child.size, child.properties.backgroundColor);

			RenderElementChildren(child);
		}
	}

	void Render() {
		RenderElementChildren(Root);
	};
};

static int ELEMENT_DEFINITION_LATCH;

#define ELEMENT(...) \
	for (ELEMENT_DEFINITION_LATCH = (UI_CONTEXT->OpenElement(__VA_ARGS__), 0); ELEMENT_DEFINITION_LATCH < 1; ++ELEMENT_DEFINITION_LATCH, UI_CONTEXT->CloseElement())

#define USERINTERFACE(name, layout) \
	UI *name = new UI();            \
	UI *UI_CONTEXT = name;          \
	layout                          \
		name->UpdateLayout();

UI *testUserinterface() {
	USERINTERFACE(testUI, ELEMENT({
							  .sizing = {FIXED(1000), FIXED(1000)},
							  .padding = {.top = 10.0f, .left = 10.0f},
							  .backgroundColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
						  }) { ELEMENT({
								   .sizing = {FIXED(500), FIXED(500)},
								   .backgroundColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
							   }); })

	return testUI;
}

#endif
