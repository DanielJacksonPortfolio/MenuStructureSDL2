#include "Slider.h"

Slider::Slider(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, int knobWidth, int knobHeight, int* value, int numberOfPoints, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, Color color2, Color color3, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);
	this->color = color;
	this->knobWidth = knobWidth;
	this->knobHeight = knobHeight;
	this->color2 = color2;
	this->color3 = color3;
	this->colorMode = colorMode;
	this->value = value;
	this->numberOfPoints = numberOfPoints;
	this->knobPos = { static_cast<float>(this->width), this->height * 0.5f };
	UpdateSlider();
}

Slider::~Slider()
{
	delete container;
	delete widgetList;
	delete value;
	for (size_t i = 0; i < widgets.size(); i++)
	{
		delete widgets[i];
	}
	for (size_t i = 0; i < displayWidgets.size(); i++)
	{
		delete displayWidgets[i];
	}
}

void Slider::Draw(SDL_Renderer* renderer, float x, float y)
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
			SDL_Rect widgetRect = { position.x, position.y, width, height };
			SDL_Rect barRect = { position.x, position.y + height * 0.45f, width, height * 0.1f };
			SDL_Rect knobRect = { position.x + knobPos.x - knobWidth * 0.5f, position.y + knobPos.y - knobHeight * 0.5f, knobWidth, knobHeight };

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			if (colorMode == FILLED)
				SDL_RenderFillRect(renderer, &widgetRect);
			SDL_SetRenderDrawColor(renderer, color2.r, color2.g, color2.b, 255);
			SDL_RenderFillRect(renderer, &barRect);
			SDL_SetRenderDrawColor(renderer, color3.r * colorMultiplier, color3.g * colorMultiplier, color3.b * colorMultiplier, 255);
			SDL_RenderFillRect(renderer, &knobRect);

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

void Slider::HoverControl(bool hovering)
{
	if (hovering && !hovered)
	{
		hovered = true;
		colorMultiplier = 0.75f;
	}
	else if (!hovering && hovered)
	{
		hovered = false;
		colorMultiplier = 1.0f;
	}
}

void Slider::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event,float x, float y)
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
			if (aboveInside && ((mousePos.x > position.x && mousePos.x < position.x + width && mousePos.y > position.y && mousePos.y < position.y + height) || (mousePos.x > position.x + knobPos.x - knobWidth * 0.5f && mousePos.x < position.x + knobPos.x + knobWidth * 0.5f && mousePos.y > position.y + knobPos.y - knobHeight * 0.5f && mousePos.y < position.y + knobPos.y + knobHeight * 0.5f)))
			{
				if (mousePos.x > position.x + knobPos.x - knobWidth * 0.5f && mousePos.x < position.x + knobPos.x + knobWidth * 0.5f && mousePos.y > position.y + knobPos.y - knobHeight * 0.5f && mousePos.y < position.y + knobPos.y + knobHeight * 0.5f)
				{
					HoverControl(true);
				}
				else
				{
					HoverControl(false);
				}
				switch (event.type)
				{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_LEFT:
						if (*value > 0)
						{
							knobPos.x -= (static_cast<float>(width) / static_cast<float>(numberOfPoints));
							UpdateSlider();
						}

						break;
					case SDLK_RIGHT:
						if (*value < numberOfPoints)
						{
							knobPos.x += (static_cast<float>(width) / static_cast<float>(numberOfPoints));
							UpdateSlider();
						}
						break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (mousePos.x > position.x + knobPos.x - knobWidth * 0.5f && mousePos.x < position.x + knobPos.x + knobWidth * 0.5f && mousePos.y > position.y + knobPos.y - knobHeight * 0.5f && mousePos.y < position.y + knobPos.y + knobHeight * 0.5f)
						{
							buttonPressed = true;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						UpdateSlider();
					}
					break;
				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0)
					{
						if (*value < numberOfPoints)
						{
							knobPos.x += (static_cast<float>(width) / static_cast<float>(numberOfPoints));
							UpdateSlider();
						}
					}
					if (event.wheel.y < 0)
					{
						if (*value > 0)
						{
							knobPos.x -= (static_cast<float>(width) / static_cast<float>(numberOfPoints));
							UpdateSlider();
						}
					}
					break;
				}
				if (buttonPressed)
				{
					knobPos.x = mousePos.x - position.x;
					if (knobPos.x < 0)
					{
						knobPos.x = 0;
					}
					else if (knobPos.x > this->width)
					{
						knobPos.x = this->width;
					}
					float relativePos = (knobPos.x / this->width) * numberOfPoints;
					*value = round(relativePos);
					for (size_t i = 0; i < widgets.size(); i++)
					{
						std::string type = typeid(*widgets[i]).name();
						type = type.substr(6);
						if (type == "Text")
						{
							widgets[i]->UpdateText(std::to_string(*value));
						}
					}
				}
			}
			else
			{
				HoverControl(false);
				if (buttonPressed)
					UpdateSlider();
			}
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
		}
	}
}

void Slider::UpdateSlider()
{
	buttonPressed = false;
	float relativePos = (knobPos.x / this->width) * numberOfPoints;
	knobPos.x = (static_cast<float>(round(relativePos)) / static_cast<float>(numberOfPoints)) * this->width;
	*value = round(relativePos);
	for (size_t i = 0; i < widgets.size(); i++)
	{
		std::string type = typeid(*widgets[i]).name();
		type = type.substr(6);
		if (type == "Text")
		{
			widgets[i]->UpdateText(std::to_string(*value));
		}
	}
}