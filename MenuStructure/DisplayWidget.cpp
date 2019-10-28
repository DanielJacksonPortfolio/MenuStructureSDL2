#include "DisplayWidget.h"

DisplayWidget::DisplayWidget()
{
}

DisplayWidget::~DisplayWidget()
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
}

void DisplayWidget::Draw(SDL_Renderer* renderer, float x, float y)
{
	if (showThis)
	{
		if (x != 0.0f || y != 0.0f)
		{
			storePosition = position;
			position.x += x;
			position.y += y;
			UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->width, this->height });
		}
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			if (texture != nullptr)
				SDL_RenderCopy(renderer, texture, &textureRect, &renderQuad);
		}
		if (x != 0.0f || y != 0.0f)
		{
			position = storePosition;
			UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->width, this->height });
		}
	}
}

void DisplayWidget::UpdatePosition(SDL_Rect renderQuad)
{
	this->renderQuad = renderQuad;
}

void DisplayWidget::UpdatePositionData(PositionType positionModeX, PositionType positionModeY, float x, float y, bool change)
{
	if (change)
	{
		LoadPositionData(ALIGNMENT_ABSOLUTE, { x, y }, positionModeX, positionModeY);
	}
	else
	{
		LoadPositionData(this->alignment, this->originalPosition, this->positionModeX, this->positionModeY);
	}
	UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->width, this->height });
}

void DisplayWidget::UpdateTextureRect(SDL_Rect textureRect)
{
	this->textureRect = textureRect;
}
