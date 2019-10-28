#pragma once
#include "Page.h"
#include "Row.h"
#include "Search.h"
#include "ScrollingList.h"
class Grid : public Page
{
private:
	int rowCount = 0;
	std::vector<Row*> rows = {};
	ScrollingList* list = nullptr;
	Widget* search = nullptr;
	RowModes rowMode = WIDGET;
public:
	Grid(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, ScrollMode scrollMode, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, int rowCount, RowModes rowMode);
	~Grid();
	void AutoAdjust() override;
	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f) override;
	void SearchWidgets(std::string searchText) override;
};

