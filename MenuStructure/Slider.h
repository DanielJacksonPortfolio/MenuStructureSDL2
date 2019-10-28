#pragma once
#include "Widget.h"
#include "Text.h"
class Slider : public Widget
{
private:
	Color color2 = { 0, 0, 0 }, color3 = { 0, 0, 0 };
	float colorMultiplier = 1.0f;
	bool hovered = false, buttonPressed = false;
	int knobWidth = 0, knobHeight = 0, numberOfPoints = 1;
	int* value = nullptr;
	Vec2 knobPos = { 0, 0 };
	SDL_Point lastMousePos = { 0, 0 };

public:
	Slider(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, int knobWidth, int knobHeight, int* value, int numberOfPoints, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, Color color2, Color color3, ColorMode colorMode);
	~Slider();
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void HoverControl(bool hovering);
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event,float x = 0.0f, float y = 0.0f) override;
	void UpdateSlider();
};

