#include "Selector.h"

Selector::Selector(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, std::function<void(std::string)> function, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);

	this->function = function;
	this->color = color;
	this->colorMode = colorMode;
	
	this->widgets.push_back(new Button(this->widgetList, this->ID + "LEFTBUTTON", this, 10, 100, [&, this]() { Left(); },nullptr,VOID, DIMENSION_PERCENTAGE, DIMENSION_PERCENTAGE, LEFT, { 0,0 }, POSITION_ABSOLUTE, POSITION_ABSOLUTE, this->color, TRANSPARENT));
	this->widgets.push_back(new Button(this->widgetList, this->ID + "RIGHTBUTTON", this, 10, 100, [&, this]() { Right(); }, nullptr, VOID, DIMENSION_PERCENTAGE, DIMENSION_PERCENTAGE, RIGHT, { 0,0 }, POSITION_ABSOLUTE, POSITION_ABSOLUTE, this->color, TRANSPARENT));
}

Selector::~Selector()
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

void Selector::AutoAdjust()
{
	options = {};
	for (size_t i = 0; i < widgets.size(); i++)
	{
		std::string type = typeid(*widgets[i]).name();
		type = type.substr(6);
		if (type == "Text")
		{
			options.push_back(widgets[i]);
		}
	}
	numberText = options.size();
	activeID = 0;
}

void Selector::Draw(SDL_Renderer* renderer, float x, float y)
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
			SDL_Rect rect = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };

			SDL_SetRenderDrawColor(renderer, color.r * colorMultiplier, color.g * colorMultiplier, color.b * colorMultiplier, 255);
			if (colorMode == FILLED)
				SDL_RenderFillRect(renderer, &rect);
			for (size_t i = 0; i < widgets.size(); i++)
			{
				std::string type = typeid(*widgets[i]).name();
				type = type.substr(6);
				if (type != "Text")
				{
					widgets[i]->Draw(renderer, x, y);
				}
				if (options.size() > 0)
					options[activeID]->Draw(renderer, x, y);
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}

void Selector::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y)
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
				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
					}
					break;
				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0)
					{
					}
					if (event.wheel.y < 0)
					{
					}
					break;
				}
			}
			for (size_t i = 0; i < widgets.size(); i++)
			{
				widgets[i]->Input(insideThis, mousePos, event, x, y);
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}

void Selector::Left()
{
	if (activeID > 1)
		activeID--;
	else
		activeID = numberText-1;

	std::invoke(function, options[activeID]->GetID());
}

void Selector::Right()
{
	activeID++;
	activeID = activeID % numberText;
	std::invoke(function, options[activeID]->GetID());
}