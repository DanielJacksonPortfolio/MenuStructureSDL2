#pragma once
#include "Page.h"
class List : public Page
{
private:
public:
	List(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode);
	~List();
	void AutoAdjust() override;
};

