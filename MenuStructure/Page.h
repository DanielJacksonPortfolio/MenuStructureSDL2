#pragma once
#include "Widget.h"
class Page : public Widget
{
protected:

public:
	Page() {}
	Page(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~Page();
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
};

