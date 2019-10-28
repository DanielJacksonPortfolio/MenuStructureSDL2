//#pragma once
//#include "DisplayWidget.h"
//#include "Text.h"
//class Textbox : public DisplayWidget
//{
//private:
//	std::string textString = "";
//	Font* font = nullptr;
//	Color baseColor = { 0,0,0 };
//	Color hoverColor = { 0,0,0 };
//	TextRenderModes renderMode = SOLID;
//	TextDisplayModes displayMode = DIMENSION_BASED;
//	DrawMode drawMode = BASE;
//	int fontSize = 0;
//	std::vector<Text*> lines = {};
//public:
//	Textbox(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, std::string textString, std::string fontPath, int fontSize, int width, int height, SDL_Renderer* renderer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color baseColor, Color hoverColor, TextRenderModes renderMode);
//	~Textbox();
//	void AutoAdjust();
//	void UpdateSize(int ptSize);
//	void UpdateImage();
//	void UpdateColor(Color color, DrawMode drawMode) override;
//	void SetDrawMode(DrawMode drawMode) override;
//	void LoadText(std::string text, TTF_Font* font, Color color, int renderMode);
//	SDL_Surface* GetTextSurface(std::string text, TTF_Font* font, Color color, int renderMode);
//	Color virtual const GetColor(DrawMode drawMode) { if (drawMode == BASE) return baseColor; else return hoverColor; }
//};