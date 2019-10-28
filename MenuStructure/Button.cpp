#include "Button.h"

Button::Button(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, std::function<void()> vFunction, std::function<void(std::string)> sFunction,FunctionModes functionMode, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);

	this->functionMode = functionMode;
	if (this->functionMode == VOID)
		this->vFunction = vFunction;
	else if(this->functionMode == STRING)
		this->sFunction = sFunction;

	this->color = color;
	this->colorMode = colorMode;
}

Button::~Button()
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

void Button::Draw(SDL_Renderer* renderer, float x, float y)
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
			SDL_SetRenderDrawColor(renderer, color.r * colorMultiplier, color.g * colorMultiplier, color.b * colorMultiplier, 255);
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


void Button::HoverControl(bool hovering)
{
	if (hovering && !hovered)
	{
		hovered = true;
		colorMultiplier = 0.75f;
		for (size_t i = 0; i < widgets.size(); i++)
		{
			std::string type = typeid(*widgets[i]).name();
			type = type.substr(6);
			if (type == "Text")
			{
				widgets[i]->SetDrawMode(HOVER);
			}
		}
	}
	else if (!hovering && hovered)
	{
		hovered = false;
		colorMultiplier = 1.0f;
		for (size_t i = 0; i < widgets.size(); i++)
		{
			std::string type = typeid(*widgets[i]).name();
			type = type.substr(6);
			if (type == "Text")
			{
				widgets[i]->SetDrawMode(BASE);
			}

		}
	}
}

void Button::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y)
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
				HoverControl(true);

				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (functionMode == VOID)
							std::invoke(vFunction);
						else if (functionMode == STRING)
							std::invoke(sFunction, this->ID);
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
			else
			{
				HoverControl(false);
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

