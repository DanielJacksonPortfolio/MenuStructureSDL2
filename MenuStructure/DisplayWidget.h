#pragma once
#include "Widget.h"
class DisplayWidget : public Widget
{
protected:
	int textureWidth = -1, textureHeight = -1;
	SDL_Rect textureRect = { 0, 0, 0, 0 }, renderQuad = { 0, 0, 0, 0 };
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
public:
	DisplayWidget();
	~DisplayWidget();

	void Draw(SDL_Renderer* renderer, float x = 0.0f, float y = 0.0f) override;
	void UpdatePosition(SDL_Rect renderQuad);
	void UpdatePositionData(PositionType positionModeX, PositionType positionModeY, float x, float y, bool change) override;
	void UpdateTextureRect(SDL_Rect renderQuad);
};

