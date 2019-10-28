#pragma once
#include "Widget.h"
#include <functional>
class Button : public Widget
{
private:
	float colorMultiplier = 1.0f;
	std::function<void()> vFunction = nullptr;
	std::function<void(std::string)> sFunction = nullptr;
	FunctionModes functionMode = VOID;
	bool hovered = false;
public:
	Button(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, std::function<void()> vFunction, std::function<void(std::string)> sFunction, FunctionModes functionMode, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~Button();
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void HoverControl(bool hovering);
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f) override;
};

