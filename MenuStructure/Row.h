#pragma once
#include "Page.h"
class Row : public Page
{
protected:
	int totalWidth = 0;
public:
	Row(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~Row();
	void AutoAdjust() override;
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f);
	void SearchWidgets(std::string searchText) override;
};

