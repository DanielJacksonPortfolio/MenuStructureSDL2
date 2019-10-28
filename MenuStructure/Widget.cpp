#include "Widget.h"

Widget::Widget()
{
}

void Widget::LoadDefaultData(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY)
{
	LoadInformation(widgetList, ID, container);
	LoadDimensionData(width, height, widthMode, heightMode);
	LoadPositionData(alignment, position, positionModeX, positionModeY);
}

void Widget::LoadDimensionData(int width, int height, DimensionType widthMode, DimensionType heightMode)
{
	this->widthMode = widthMode;
	this->heightMode = heightMode;

	switch (this->widthMode)
	{
	case DIMENSION_ABSOLUTE:
		this->width = width; break;
	case DIMENSION_PERCENTAGE:
		this->width = roundUp((this->container->GetWidth() * (width * 0.01f)), 1); break;
	}

	switch (this->heightMode)
	{
	case DIMENSION_ABSOLUTE:
		this->height = height; break;
	case DIMENSION_PERCENTAGE:
		this->height = roundUp((this->container->GetHeight() * (height * 0.01f)), 1); break;
	}

}

void Widget::LoadInformation(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container)
{
	this->widgetList = widgetList;
	this->ID = ID;
	(*widgetList)[ID] = this;
	this->container = container;
}

void Widget::LoadPositionData(AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY)
{
	this->alignment = alignment;
	this->positionModeX = positionModeX;
	this->positionModeY = positionModeY;
	this->originalPosition = position;

	switch (this->alignment)
	{
	case TOP_LEFT:
		this->position = { 0, 0 }; break;
	case TOP:
		this->position = { this->container->GetWidth() * 0.5f - this->width * 0.5f, 0 }; break;
	case TOP_RIGHT:
		this->position = { static_cast<float>(this->container->GetWidth() - this->width), 0 }; break;
	case LEFT:
		this->position = { 0, this->container->GetHeight() * 0.5f - this->height * 0.5f }; break;
	case CENTRE:
		this->position = { this->container->GetWidth() * 0.5f - this->width * 0.5f, this->container->GetHeight() * 0.5f - this->height * 0.5f };		break;
	case RIGHT:
		this->position = { static_cast<float>(this->container->GetWidth() - this->width), static_cast<float>(this->container->GetHeight() * 0.5f - this->height * 0.5f) }; break;
	case BOTTOM_LEFT:
		this->position = { 0, static_cast<float>(this->container->GetHeight() - this->height) }; break;
	case BOTTOM:
		this->position = { static_cast<float>(this->container->GetWidth() * 0.5f - this->width * 0.5f), static_cast<float>(this->container->GetHeight() - this->height) }; break;
	case BOTTOM_RIGHT:
		this->position = { static_cast<float>(this->container->GetWidth() - this->width), static_cast<float>(this->container->GetHeight() - this->height) }; break;
	case ALIGNMENT_ABSOLUTE:
		switch (this->positionModeX)
		{
		case POSITION_ABSOLUTE:
			this->position.x = originalPosition.x; break;
		case POSITION_PERCENTAGE_LEFT:
			this->position.x = roundUp((this->container->GetWidth() * (originalPosition.x * 0.01f)), 1); break;
		case POSITION_PERCENTAGE_CENTRE:
			this->position.x = roundUp((this->container->GetWidth() * (originalPosition.x * 0.01f)), 1) - this->width * 0.5f; break;
		case POSITION_PERCENTAGE_RIGHT:
			this->position.x = roundUp((this->container->GetWidth() * (originalPosition.x * 0.01f)), 1) - this->width; break;
		}
		switch (this->positionModeY)
		{
		case POSITION_ABSOLUTE:
			this->position.y = originalPosition.y; break;
		case POSITION_PERCENTAGE_LEFT:
			this->position.y = roundUp((this->container->GetHeight() * (originalPosition.y * 0.01f)), 1); break;
		case POSITION_PERCENTAGE_CENTRE:
			this->position.y = roundUp((this->container->GetHeight() * (originalPosition.y * 0.01f)), 1) - this->height * 0.5f; break;
		case POSITION_PERCENTAGE_RIGHT:
			this->position.y = roundUp((this->container->GetHeight() * (originalPosition.y * 0.01f)), 1) - this->height; break;
		}
		break;
	}

	this->position.x += this->container->GetPos().x;
	this->position.y += this->container->GetPos().y;
}


Widget::~Widget()
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
}

void Widget::Draw(SDL_Renderer* renderer, float x, float y)
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

void Widget::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y) 
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
};

void Widget::Update()
{
	if (showThis)
	{
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			for (size_t i = 0; i < widgets.size(); i++)
			{
				widgets[i]->Update();
			}
		}
	}
}

void Widget::UpdatePositionData(PositionType positionModeX, PositionType positionModeY, float x, float y, bool change)
{
	if (change)
	{
		LoadPositionData(ALIGNMENT_ABSOLUTE, { x, y }, positionModeX, positionModeY);
		change = false;
	}
	else
	{
		LoadPositionData(this->alignment, this->originalPosition, this->positionModeX, this->positionModeY);
	}
	for (size_t i = 0; i < widgets.size(); i++)
	{
		widgets[i]->UpdatePositionData(positionModeX, positionModeY, x, y, change);
	}
}
