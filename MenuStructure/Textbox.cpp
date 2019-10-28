//#include "Textbox.h"
//
//Textbox::Textbox(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, std::string textString, std::string fontPath, int fontSize, int width, int height, SDL_Renderer* renderer, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color baseColor, Color hoverColor, TextRenderModes renderMode)
//{
//	LoadInformation(widgetList, ID, container);
//
//	this->displayMode = displayMode;
//
//	this->textString = textString;
//	this->font = new Font(fontPath, fontSize);
//	this->fontSize = fontSize;
//	this->baseColor = baseColor;
//	this->hoverColor = hoverColor;
//	this->renderMode = renderMode;
//	this->renderer = renderer;
//
//	UpdateImage();
//
//	LoadDimensionData(width, height, widthMode, heightMode);
//
//	this->width = textureWidth;
//	this->height = textureHeight;
//
//	LoadPositionData(alignment, position, positionModeX, positionModeY);
//
//	UpdateImage();
//}
//
//
//Textbox::~Textbox()
//{
//}
//
//void Textbox::AutoAdjust()
//{
//	
//
//	//int widgetH = 0;
//	//for (size_t i = 0; i < widgets.size(); i++)
//	//{
//	//	widgetH += widgets[i]->GetHeight();
//	//}
//	//int spare = this->height - widgetH;
//	//float gap = spare / (widgets.size() + 1);
//	//float pos = gap;
//	//for (size_t i = 0; i < widgets.size(); i++)
//	//{
//	//	widgets[i]->UpdatePositionData(this->internalAlignment, POSITION_PERCENTAGE_CENTRE, POSITION_ABSOLUTE, 50, pos);
//	//	pos += gap;
//	//	pos += widgets[i]->GetHeight();
//	//}
//}
//
//Text::~Text()
//{
//	delete container;
//	delete widgetList;
//	delete font;
//	for (size_t i = 0; i < widgets.size(); i++)
//	{
//		delete widgets[i];
//	}
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyTexture(texture);
//}
//
//void Text::UpdateSize(int ptSize)
//{
//	font->UpdateSize(ptSize);
//	UpdateImage();
//}
//
//void Text::UpdateImage()
//{
//	if (drawMode == HOVER)
//		LoadText(textString, font->font, hoverColor, renderMode);
//	else
//		LoadText(textString, font->font, baseColor, renderMode);
//	UpdatePosition({ static_cast<int>(this->position.x),static_cast<int>(this->position.y),this->textureWidth,this->textureHeight });
//}
//
//SDL_Surface* Text::GetTextSurface(std::string text, TTF_Font* font, Color color, int renderMode)
//{
//	switch (renderMode)
//	{
//	case SOLID:
//		return TTF_RenderText_Solid(font, text.c_str(), { static_cast<Uint8>(color.r),static_cast<Uint8>(color.g),static_cast<Uint8>(color.b) });
//		//case SHADED:
//			//return TTF_RenderText_Shaded(font, text.c_str(), colors[color], colors[color2]);
//	case BLENDED:
//		return TTF_RenderText_Blended(font, text.c_str(), { static_cast<Uint8>(color.r),static_cast<Uint8>(color.g),static_cast<Uint8>(color.b) });
//		//case WRAPPED:
//			//return TTF_RenderText_Blended_Wrapped(font, text.c_str(), { color.r,color.b,color.g }, static_cast<Uint32>(wrapLength));
//	default:
//		return TTF_RenderText_Solid(font, text.c_str(), { static_cast<Uint8>(color.r),static_cast<Uint8>(color.g),static_cast<Uint8>(color.b) });
//	}
//}
//
//void Text::LoadText(std::string text, TTF_Font* font, Color color, int renderMode)
//{
//	if (texture != nullptr)
//	{
//		SDL_DestroyTexture(texture);
//	}
//	SDL_Surface* surface = GetTextSurface(text, font, color, renderMode);
//
//	if (surface == nullptr)
//	{
//		std::cout << "Text Load failed" << std::endl;
//	}
//	else
//	{
//		textureWidth = surface->w;
//		textureHeight = surface->h;
//		texture = SDL_CreateTextureFromSurface(renderer, surface);
//		if (texture == nullptr)
//		{
//			std::cout << "Texture Creation Failed: %s! SDL Error: %s\n" << text.c_str() << SDL_GetError() << std::endl;
//		}
//
//		SDL_FreeSurface(surface);
//	}
//
//	UpdateTextureRect({ 0,0,textureWidth,textureHeight });
//}
//
//void Text::UpdateColor(Color color, DrawMode drawMode)
//{
//	if (drawMode == HOVER)
//		this->hoverColor = color;
//	else
//		this->baseColor = color;
//	UpdateImage();
//}
//
//void Text::SetDrawMode(DrawMode drawMode)
//{
//	this->drawMode = drawMode;
//	UpdateImage();
//}