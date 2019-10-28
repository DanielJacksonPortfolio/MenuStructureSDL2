#pragma once
#include "DisplayWidget.h"
class Image : public DisplayWidget
{
private:
	std::string imagePath = "";
	int rectW = -1, rectH = -1, rectX = -1, rectY = -1;
	ImageLoadModes imageLoadMode = ORIGINAL;
public:
	Image(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, int rectW, int rectH, int rectX, int rectY, std::string imageLocation, SDL_Renderer* renderer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, ImageLoadModes imageLoadMode);
	~Image();
	void LoadImage(std::string path);
};

