#include "Image.h"
#include <SDL_image.h>

Image::Image(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, int rectW, int rectH, int rectX, int rectY, std::string imageLocation, SDL_Renderer* renderer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, ImageLoadModes imageLoadMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);
	this->renderer = renderer;
	this->rectW = rectW;
	this->rectH = rectH;
	this->rectX = rectX;
	this->rectY = rectY;
	this->imageLoadMode = imageLoadMode;
	LoadImage(imageLocation);
	switch (this->imageLoadMode)
	{
	case STRETCH:
		break;
	case ORIGINAL:
		this->width = textureWidth;
		this->height = textureHeight;
		break;
	case EXACT:
		UpdateTextureRect({ this->rectX, this->rectY, this->rectW, this->rectH });
		break;
	}
	UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->width, this->height });
}

Image::~Image()
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

void Image::LoadImage(std::string path)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == nullptr)
	{
		std::cout << "Image Load failed: %s! SDL_image Error: %s\n" << path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
		textureWidth = surface->w;
		textureHeight = surface->h;
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr)
		{
			std::cout << "Texture Creation Failed: %s! SDL Error: %s\n" << path.c_str() << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(surface);
	}

	UpdateTextureRect({ 0, 0, textureWidth, textureHeight });
}