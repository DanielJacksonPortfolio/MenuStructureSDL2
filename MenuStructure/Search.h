#pragma once
#include "Widget.h"
#include "Text.h"
class Search : public Widget
{
private:
	float colorMultiplier = 1.0f;
	bool hovered = false, active = false;;

	Widget* searchContainer = nullptr;
	std::string searchText = "", displayText = "";
	int maxLength = 0;
public:
	Search(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int maxLength, int width, int height, Widget* searchContainer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~Search();
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void HoverControl(bool hovering);
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f) override;
};

