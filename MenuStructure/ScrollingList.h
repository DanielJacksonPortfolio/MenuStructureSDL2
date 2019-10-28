#pragma once
#include "Page.h"
#include "List.h"
class ScrollingList : public Page
{
private:
	int pageCount = 0, showList = 0;
	float viewY = 0.0f, totalHeight = 0.0f;
	std::vector<List*> lists = {};
	int displayWidgetAmount = 0;
	ScrollMode scrollMode = SMOOTH;
public:
	ScrollingList(std::unordered_map<std::string, Widget* > * widgetList, std::string ID, Widget* container, ScrollMode scrollMode, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~ScrollingList();
	void AutoAdjust() override;
	void Draw(SDL_Renderer* renderer,float x = 0.0f, float y = 0.0f) override;
	void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f) override;
	void SearchWidgets(std::string searchText) override;
};

