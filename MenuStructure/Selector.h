#pragma once
#include "Widget.h"
#include "Text.h"
#include "Button.h"
#include <functional>
class Selector : public Widget
{
private:
	float colorMultiplier = 1.0f;
	std::function<void(std::string)> function;
	std::vector<Widget*> options = {};
	int activeID = 0, numberText = 0;
public:
	Selector(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, std::function<void(std::string)> function, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~Selector();
	void AutoAdjust() override;
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f) override;
	void Left();
	void Right();
};

