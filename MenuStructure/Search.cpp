#include "Search.h"

Search::Search(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int maxLength, int width, int height, Widget* searchContainer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);
	this->searchContainer = searchContainer;
	this->color = color;
	this->colorMode = colorMode;
	this->maxLength = maxLength;
}

Search::~Search()
{
	delete searchContainer;
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

void Search::Draw(SDL_Renderer* renderer, float x, float y)
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


void Search::HoverControl(bool hovering)
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

void Search::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y)
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
						if (active)
						{
							HoverControl(false);
							active = false;
						}
						else
						{
							HoverControl(true);
							active = true;
						}
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
				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						HoverControl(false);
						active = false;
					}
					break;
				}
			}
			if (active)
			{
				bool changeMade = false;
				switch (event.type)
				{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_BACKSPACE:
						if (searchText.length() > 0)
						{
							searchText.pop_back();
							changeMade = true;
						}
						break;
					case SDLK_SPACE:
						searchText += " "; changeMade = true; break;
					case SDLK_a:
						searchText += "A"; changeMade = true; break;
					case SDLK_b:
						searchText += "B"; changeMade = true; break;
					case SDLK_c:
						searchText += "C"; changeMade = true; break;
					case SDLK_d:
						searchText += "D"; changeMade = true; break;
					case SDLK_e:
						searchText += "E"; changeMade = true; break;
					case SDLK_f:
						searchText += "F"; changeMade = true; break;
					case SDLK_g:
						searchText += "G"; changeMade = true; break;
					case SDLK_h:
						searchText += "H"; changeMade = true; break;
					case SDLK_i:
						searchText += "I"; changeMade = true; break;
					case SDLK_j:
						searchText += "J"; changeMade = true; break;
					case SDLK_k:
						searchText += "K"; changeMade = true; break;
					case SDLK_l:
						searchText += "L"; changeMade = true; break;
					case SDLK_m:
						searchText += "M"; changeMade = true; break;
					case SDLK_n:
						searchText += "N"; changeMade = true; break;
					case SDLK_o:
						searchText += "O"; changeMade = true; break;
					case SDLK_p:
						searchText += "P"; changeMade = true; break;
					case SDLK_q:
						searchText += "Q"; changeMade = true; break;
					case SDLK_r:
						searchText += "R"; changeMade = true; break;
					case SDLK_s:
						searchText += "S"; changeMade = true; break;
					case SDLK_t:
						searchText += "T"; changeMade = true; break;
					case SDLK_u:
						searchText += "U"; changeMade = true; break;
					case SDLK_v:
						searchText += "V"; changeMade = true; break;
					case SDLK_w:
						searchText += "W"; changeMade = true; break;
					case SDLK_x:
						searchText += "X"; changeMade = true; break;
					case SDLK_y:
						searchText += "Y"; changeMade = true; break;
					case SDLK_z:
						searchText += "Z"; changeMade = true; break;
					case SDLK_0:
						searchText += "0"; changeMade = true; break;
					case SDLK_1:
						searchText += "1"; changeMade = true; break;
					case SDLK_2:
						searchText += "2"; changeMade = true; break;
					case SDLK_3:
						searchText += "3"; changeMade = true; break;
					case SDLK_4:
						searchText += "4"; changeMade = true; break;
					case SDLK_5:
						searchText += "5"; changeMade = true; break;
					case SDLK_6:
						searchText += "6"; changeMade = true; break;
					case SDLK_7:
						searchText += "7"; changeMade = true; break;
					case SDLK_8:
						searchText += "8"; changeMade = true; break;
					case SDLK_9:
						searchText += "9"; changeMade = true; break;
					}
					break;
				}
				if (changeMade)
				{
					for (size_t i = 0; i < widgets.size(); i++)
					{
						std::string type = typeid(*widgets[i]).name();
						type = type.substr(6);
						if (type == "Text")
						{
							if (searchText.length() > 0)
							{
								if (searchText.length() > maxLength)
								{
									displayText = searchText.substr(searchText.length() - maxLength);
								}
								else
								{
									displayText = searchText;
								}
							}
							else
							{
								displayText = "Search...";
							}
							widgets[i]->UpdateText(displayText);
						}
					}
					this->searchContainer->SearchWidgets(searchText);
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
