#include "Page.h"

Page::Page(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);

	this->color = color;
	this->colorMode = colorMode;
}

Page::~Page()
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

void Page::Draw(SDL_Renderer* renderer, float x, float y)
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
			for (size_t i = 0; i < widgets.size(); i++)
			{
				widgets[i]->Draw(renderer, x, y);
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}
