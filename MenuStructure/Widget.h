#pragma once
#include "UIConstants.h"
#include "Font.h"
#include <unordered_map>
#include <SDL.h>
#include <functional>
#include <iostream>

class Widget
{
protected:
	std::string ID = "NULL";
	int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
	Vec2 originalPosition = { 0, 0 }, position = { 0, 0 };
	Color color = { 0, 0, 0 };
	Widget* container = nullptr;
	AlignmentType alignment = ALIGNMENT_ABSOLUTE;
	DimensionType widthMode = DIMENSION_ABSOLUTE, heightMode = DIMENSION_ABSOLUTE;
	PositionType positionModeX = POSITION_ABSOLUTE, positionModeY = POSITION_ABSOLUTE;
	ColorMode colorMode = FILLED;
	std::vector<Widget*> widgets = {}, displayWidgets = {};
	std::unordered_map<std::string, Widget*> * widgetList = nullptr;
	Vec2 storePosition = { 0,0 };
	bool showThis = true;

public:
	Widget();
	virtual ~Widget();

	void LoadDefaultData(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY);
	void LoadDimensionData(int width, int height, DimensionType widthMode, DimensionType heightMode);
	void LoadPositionData(AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY);
	void LoadInformation(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container);
	
	std::vector<Widget*> * GetWidgets()			{ return &widgets; }
	std::vector<Widget*> * GetDisplayWidgets()	{ return &displayWidgets; }
	const AlignmentType GetAlignment()			{ return alignment; }
	const int GetWidth()						{ return width; }
	const int GetHeight()						{ return height; }
	const Vec2 GetPos()							{ return position; }
	const std::string GetID()					{ return ID; }
	const Color	GetColor()						{ return { 0, 0, 0 }; }

	bool GetShow() 
	{ 
		return this->showThis;
	}

	void SetShow(bool showThis)					
	{ 
		this->showThis = showThis; 		
		for (size_t i = 0; i < widgets.size(); i++)
		{
			widgets[i]->SetShow(showThis);
		}
	}
	void SetContainer(Widget* container)		{ this->container = container; LoadPositionData(this->alignment, this->originalPosition, this->positionModeX, this->positionModeY); }
	void SetAllWidgets()						{ this->displayWidgets = this->widgets; AutoAdjust(); }
	void ShowAllWidgets()						{ this->displayWidgets = this->widgets; }
	void ClearWidgets()								
	{
		int size = widgets.size();
		for (size_t i = 0; i < size; i++)
		{
			std::string widgetID = widgets[0]->GetID();
			(*widgetList).erase(widgetID);
			this->widgets.erase(widgets.begin());
		}
	}

	void AddPage			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode );
	void AddRow				(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode );
	void AddList			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode );
	void AddScrollingList	(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, ScrollMode scrollMode);
	void AddGrid			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, ScrollMode scrollMode, int rowCount, RowModes rowMode);
	void AddButton			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::function<void()> vFunction, std::function<void(std::string)> sFunction, FunctionModes functionMode,	Color color, ColorMode colorMode);
	void AddSelector		(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::function<void(std::string)> function,Color color, ColorMode colorMode);
	void AddSearch			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int maxLength, Widget* searchContainer, Color color, ColorMode colorMode);
	void AddSlider			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int knobWidth, int knobHeight, int* value, int numberOfPoints,																 Color color, Color color2, Color color3, ColorMode colorMode);
	void AddText			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::string textString, Font* font, std::string fontPath, int fontSize, SDL_Renderer* renderer, TextDisplayModes displayMode, Color baseColor, Color hoverColor, TextRenderModes renderMode);
	void AddImage			(std::unordered_map<std::string, Widget*> * widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int rectW, int rectH, int rectX, int rectY, std::string imageLocation, SDL_Renderer* renderer, ImageLoadModes imageLoadMode);

	virtual void Draw(SDL_Renderer * renderer, float x = 0.0f, float y = 0.0f);
	virtual void Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x = 0.0f, float y = 0.0f);
	virtual void Update();
	virtual void UpdatePositionData(PositionType positionModeX, PositionType positionModeY, float x, float y, bool change);

	virtual void AutoAdjust() {}
	virtual void SearchWidgets(std::string searchText) {}
	virtual void SetDrawMode(DrawMode drawMode) {};
	virtual void UpdateColor(Color color, DrawMode drawMode) {}
	virtual void UpdateText(std::string newText) {}
};
