#include "Row.h"


Row::Row(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);

	this->color = color;
	this->colorMode = colorMode;
}

Row::~Row()
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

void Row::AutoAdjust()
{
	if (displayWidgets.size() > 0)
	{
		int widgetW = 0;
		for (size_t i = 0; i < displayWidgets.size(); i++)
		{
			widgetW += displayWidgets[i]->GetWidth();
		}
		int spare = this->width - widgetW;
		float gap = spare / (displayWidgets.size() + 1);
		float pos = gap;
		for (size_t i = 0; i < displayWidgets.size(); i++)
		{
			displayWidgets[i]->UpdatePositionData(POSITION_ABSOLUTE, POSITION_PERCENTAGE_CENTRE, pos, 50, true);
			pos += gap;
			pos += displayWidgets[i]->GetWidth();
		}
		totalWidth = pos;
	}
}

void Row::Draw(SDL_Renderer* renderer, float x, float y)
{
	if (showThis)
	{
		if (x != 0.0f || y != 0.0f)
		{
			storePosition = position;
			position.x += x;
			position.y += y;
		}
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			SDL_Rect rect = { position.x, position.y, width, height };

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			if (colorMode == FILLED)
				SDL_RenderFillRect(renderer, &rect);
			for (size_t i = 0; i < displayWidgets.size(); i++)
			{
				displayWidgets[i]->Draw(renderer, x, y);
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}

void Row::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y)
{
	if (showThis)
	{
		if (x != 0.0f || y != 0.0f)
		{
			storePosition = position;
			position.x += x;
			position.y += y;
		}
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			bool insideThis = false;
			if (aboveInside && mousePos.x > position.x && mousePos.x < position.x + width && mousePos.y > position.y && mousePos.y < position.y + height)
			{
				insideThis = true;
			}
			for (size_t i = 0; i < displayWidgets.size(); i++)
			{
				displayWidgets[i]->Input(insideThis, mousePos, event, x, y);
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}

void Row::SearchWidgets(std::string searchText)
{
	displayWidgets = {};
	for (size_t i = 0; i < widgets.size(); i++)
	{
		std::string widgetID = widgets[i]->GetID();
		std::transform(widgetID.begin(), widgetID.end(), widgetID.begin(), ::toupper);
		if (widgetID.substr(0, searchText.length()) == searchText || searchText.length() == 0 || searchText == " ")
		{
			displayWidgets.push_back(widgets[i]);
		}
	}
	AutoAdjust();
}