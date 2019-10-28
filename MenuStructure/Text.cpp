#include "Text.h"

void Text::InitTextData()
{
	switch (this->displayMode)
	{
	case CONTAINER:
		this->width = this->container->GetWidth();
		this->height = this->container->GetHeight();
	case DIMENSION_BASED:
		UpdateSize(1);
		this->fontSize = 1;
		while (textureWidth < this->width && textureHeight < this->height)
		{
			UpdateSize(++this->fontSize);
		}
		UpdateSize(--this->fontSize);
		this->width = textureWidth;
		this->height = textureHeight;
		break;
	case CUTOFF:
		if (textureWidth > this->width)
		{
			if (textureHeight < this->height)
			{
				this->height = textureHeight;
			}
			UpdateTextureRect({ 0, 0, this->width, this->height });

		}
		else
		{
			this->width = textureWidth;

			if (textureHeight > this->height)
			{
				UpdateTextureRect({ 0, 0, this->width, this->height });
			}
			else
			{
				this->height = textureHeight;
			}

		}
		UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->width, this->height });
		break;
	case DISABLE_RESTRAINTS:
		this->width = textureWidth;
		this->height = textureHeight;
		break;
	case TEXT_EXACT:
		break;
	}

}

Text::Text(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, std::string textString, Font* font, std::string fontPath, int fontSize, int width, int height, SDL_Renderer* renderer, TextDisplayModes displayMode, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color baseColor, Color hoverColor, TextRenderModes renderMode)
{
	LoadInformation(widgetList, ID, container);

	this->displayMode = displayMode;

	this->textString = textString;
	if (font == nullptr)
		this->font = new Font(fontPath, fontSize);
	else
		this->font = font;
	this->fontSize = fontSize;
	this->baseColor = baseColor;
	this->hoverColor = hoverColor;
	this->renderMode = renderMode;
	this->renderer = renderer;

	UpdateImage();

	LoadDimensionData(width, height, widthMode, heightMode);

	InitTextData();

	LoadPositionData(alignment, position, positionModeX, positionModeY);

	UpdateImage();
}

Text::~Text()
{
	delete container;
	delete widgetList;
	delete font;
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

Color const Text::GetColor(DrawMode drawMode)
{
	if (drawMode == BASE)
		return baseColor;
	else
		return hoverColor;
}

SDL_Surface* Text::GetTextSurface(std::string text, TTF_Font* font, Color color, int renderMode)
{
	switch (renderMode)
	{
	case SOLID:
		return TTF_RenderText_Solid(font, text.c_str(), { static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b) });
		//case SHADED:
			//return TTF_RenderText_Shaded(font, text.c_str(), colors[color], colors[color2]);
	case BLENDED:
		return TTF_RenderText_Blended(font, text.c_str(), { static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b) });
		//case WRAPPED:
			//return TTF_RenderText_Blended_Wrapped(font, text.c_str(), { color.r, color.b, color.g }, static_cast<Uint32>(wrapLength));
	default:
		return TTF_RenderText_Solid(font, text.c_str(), { static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b) });
	}
}

void Text::LoadText(std::string text, TTF_Font* font, Color color, int renderMode)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface = GetTextSurface(text, font, color, renderMode);

	if (surface == nullptr)
	{
		std::cout << "Text Load failed" << std::endl;
	}
	else
	{
		textureWidth = surface->w;
		textureHeight = surface->h;
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr)
		{
			std::cout << "Texture Creation Failed: %s! SDL Error: %s\n" << text.c_str() << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(surface);
	}

	UpdateTextureRect({ 0, 0, textureWidth, textureHeight });
}

void Text::SetDrawMode(DrawMode drawMode)
{
	this->drawMode = drawMode;
	UpdateImage();
}

void Text::UpdateColor(Color color, DrawMode drawMode)
{
	if (drawMode == HOVER)
		this->hoverColor = color;
	else
		this->baseColor = color;
	UpdateImage();
}

void Text::UpdateImage()
{
	if (drawMode == HOVER)
		LoadText(textString, font->font, hoverColor, renderMode);
	else
		LoadText(textString, font->font, baseColor, renderMode);
	UpdatePosition({ static_cast<int>(this->position.x), static_cast<int>(this->position.y), this->textureWidth, this->textureHeight });
}

void Text::UpdateSize(int ptSize)
{
	font->UpdateSize(ptSize);
	UpdateImage();
}

void Text::UpdateText(std::string newText)
{
	this->textString = newText;
	//LoadInformation(widgetList, ID, container);

	UpdateImage();

	LoadDimensionData(width, height, widthMode, heightMode);

	InitTextData();

	LoadPositionData(alignment, this->originalPosition, positionModeX, positionModeY);

	UpdateImage();
	
	//UpdateImage();
	//this->width = textureWidth;
	//this->height = textureHeight;
}

