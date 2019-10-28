#include "List.h"

List::List(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);
	this->color = color;
	this->colorMode = colorMode;
}

List::~List()
{
	delete container;
	delete widgetList;
	for (size_t i = 0; i < widgets.size(); i++)
	{
		delete widgets[i];
	}
	for (size_t i = 0; i < displayWidgets.size(); i++)
	{
		delete displayWidgets[i];
	}
}

void List::AutoAdjust()
{
	int widgetH = 0;
	for (size_t i = 0; i < widgets.size(); i++)
	{
		widgetH += widgets[i]->GetHeight();
	}
	int spare = this->height - widgetH;
	float gap = spare / (widgets.size()+1);
	float pos = gap;
	for (size_t i = 0; i < widgets.size(); i++)
	{
		widgets[i]->UpdatePositionData(POSITION_PERCENTAGE_CENTRE, POSITION_ABSOLUTE, 50, pos, true);
		pos += gap;
		pos += widgets[i]->GetHeight();
	}
}