#pragma once
#include "DisplayWidget.h"
#include "Font.h"
class Text : public DisplayWidget
{
private:
	std::string textString = "";
	int fontSize = 0;
	Color baseColor = { 0, 0, 0 }, hoverColor = { 0, 0, 0 };
	Font* font = nullptr;
	TextRenderModes renderMode = SOLID;
	TextDisplayModes displayMode = DIMENSION_BASED;
	DrawMode drawMode = BASE;

public:
	Text(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, std::string textString, Font* font, std::string fontPath, int fontSize, int width, int height, SDL_Renderer* renderer, TextDisplayModes displayMode, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color baseColor, Color hoverColor, TextRenderModes renderMode);
	~Text();
	Color const GetColor(DrawMode drawMode);
	SDL_Surface* GetTextSurface(std::string text, TTF_Font* font, Color color, int renderMode);
	void LoadText(std::string text, TTF_Font* font, Color color, int renderMode);
	void SetDrawMode(DrawMode drawMode) override;
	void UpdateColor(Color color, DrawMode drawMode) override;
	void UpdateImage();
	void UpdateSize(int ptSize);
	void UpdateText(std::string newText) override;
	void InitTextData();
};

