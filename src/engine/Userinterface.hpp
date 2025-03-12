#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Input.hpp"
#include <algorithm>
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
	LAYOUT_DIRECTION layoutDirection = DIRECTION_HORIZONTAL;
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
	UI(UIElementProperties props) : Root(CreateElem(props)) {}

	static UIElement CreateElem(UIElementProperties properties) {
		UIElement elem = {
			.properties = properties,
		};
		if (elem.properties.sizing.xAxis.type == SIZING_TYPE_FIXED) {
			elem.size.x = elem.properties.sizing.xAxis.minMax.max;
		}
		if (elem.properties.sizing.yAxis.type == SIZING_TYPE_FIXED) {
			elem.size.y = elem.properties.sizing.yAxis.minMax.max;
		}
		return elem;
	}

	void OpenElement(UIElementProperties properties) {
		UIElement elem = CreateElem(properties);

		currentElement->children.push_back(elem);
		currentElement->children.back().parent = currentElement;
		currentElement = &currentElement->children.back();
	};
	void CloseElement() {
		CalculateFitSizingWidths(currentElement);
		CalculateFitSizingHeights(currentElement);
		currentElement = currentElement->parent;
	}

	void CalculateFitSizingWidths(UIElement *elem) {
		UIElement *parent = elem->parent;
		Padding padding = elem->properties.padding;
		elem->size.x += padding.left + padding.right;

		if (parent->properties.layoutDirection == DIRECTION_HORIZONTAL) {
			parent->size.x += elem->size.x;
		}
		if (parent->properties.layoutDirection == DIRECTION_VERTICAL) {
			parent->size.x = std::max(parent->size.x, elem->size.x);
		}
	}
	void CalculateFitSizingHeights(UIElement *elem) {
		UIElement *parent = elem->parent;
		Padding padding = elem->properties.padding;
		elem->size.y += padding.top + padding.bottom;

		if (parent->properties.layoutDirection == DIRECTION_HORIZONTAL) {
			parent->size.y = std::max(parent->size.y, elem->size.y);
		}
		if (parent->properties.layoutDirection == DIRECTION_VERTICAL) {
			parent->size.y += elem->size.y;
		}
	}

	void CalculateGrowAndShrinkSizingWidths() {}
	void CalculateGrowAndShrinkSizingHeights() {}

	void WrapText() {}

	void CalculatePositions() {}

	void UpdateLayout() {
		// CalculateFitSizingWidths();
		// CalculateGrowAndShrinkSizingWidths();
		// WrapText();
		//
		// CalculateFitSizingHeights();
		// CalculateGrowAndShrinkSizingHeights();
		//
		// CalculatePositions();
	}

	void RenderElementChildren(UIElement elem, glm::vec2 positionOffset) {
		float leftOffset = elem.properties.padding.left;
		if (elem.children.empty())
			return;

		for (auto child : elem.children) {
			glm::vec2 childPosition = elem.position + child.position + positionOffset;
			childPosition.x += leftOffset;
			childPosition.y += elem.properties.padding.top;

			Quad quad = Quad();
			quad.Render(childPosition, child.size, child.properties.backgroundColor);
			leftOffset += child.size.x + elem.properties.childGap;
			RenderElementChildren(child, childPosition);
		}
	}

	void Render() {
		Quad quad = Quad();
		RenderElementChildren(Root, Root.position);
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
							  .padding = {20.0f, 20.0f, 20.0f, 20.0f},
							  .childGap = 20.0f,
							  .backgroundColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
						  }) { ELEMENT({
								   .sizing = {FIXED(100), FIXED(50)},
								   .backgroundColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),

							   }); 
                                ELEMENT({
								   .sizing = {FIXED(100), FIXED(50)},
								   .backgroundColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),

							   }); })

	return testUI;
}

#endif
