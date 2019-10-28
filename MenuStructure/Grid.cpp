#include "Grid.h"
#include <algorithm>
#include <string>

Grid::Grid(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, ScrollMode scrollMode, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, int rowCount, RowModes rowMode)
{
	LoadDefaultData(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY);
	this->color = color;
	this->colorMode = colorMode;
	this->rowMode = rowMode;
	switch (this->rowMode)
	{
	case WIDGET:
	case PIXEL:
		this->rowCount = rowCount;
		break;
	case PERCENTAGE:
		this->rowCount = roundUp((this->container->GetWidth() * (rowCount * 0.01f)), 1);
		break;
	}
	this->list = new ScrollingList(this->widgetList, this->ID + " - List ", this, SMOOTH, 100, 100, DIMENSION_PERCENTAGE, DIMENSION_PERCENTAGE, this->alignment, { 0, 0 }, POSITION_ABSOLUTE, POSITION_ABSOLUTE, this->color, this->colorMode);

}


Grid::~Grid()
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
	for (size_t i = 0; i < rows.size(); i++)
	{
		delete rows[i];
	}
	delete search;
	delete list;
}

void Grid::AutoAdjust()
{
	rows = {};
	if (displayWidgets.size() > 0)
	{
		switch (rowMode)
		{
		case WIDGET:
			int widgetCount = 0;
			int numberOfRows = ceil(static_cast<float>(displayWidgets.size()) / rowCount);
			for (int j = 0; j < numberOfRows; j++)
			{
				rows.push_back(new Row(widgetList, ID + "ROW" + std::to_string(j), this, 100, 100, DIMENSION_PERCENTAGE, DIMENSION_ABSOLUTE, ALIGNMENT_ABSOLUTE, { 50, 0 }, POSITION_PERCENTAGE_CENTRE, POSITION_ABSOLUTE, color, colorMode));
				for (int i = 0; i < rowCount; i++)
				{
					if (widgetCount < displayWidgets.size())
					{
						(*rows[j]->GetWidgets()).push_back(displayWidgets[widgetCount++]);
						(*rows[j]->GetWidgets())[i]->SetContainer(rows[j]);
					}
					else
					{
						break;
					}
				}
			}
			break;
			//case PIXEL:
			//	break;
			//case PERCENTAGE:
			//	break;
			//default:
			//	break;
		}
	}
	(*list->GetWidgets()) = {};
	if (search != nullptr)
	{
		(*list->GetWidgets()).push_back(search);
		(*list->GetWidgets()).back()->SetContainer(list);
	}
	if (rows.size() > 0)
	{
		for (int i = 0; i < rows.size(); i++)
		{
			rows[i]->SetAllWidgets();
			(*list->GetWidgets()).push_back(rows[i]);
		}
	}
	list->SetAllWidgets();
}

void Grid::Draw(SDL_Renderer* renderer, float x, float y)
{
	if (showThis)
	{
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			list->Draw(renderer);
		}
	}
}

void Grid::Input(bool aboveInside, SDL_Point mousePos, SDL_Event event, float x, float y)
{
	if (showThis)
	{
		if (position.x > -width && position.x < WINDOW_WIDTH && position.y > -height && position.y < WINDOW_HEIGHT)
		{
			bool insideThis = false;
			if (aboveInside && mousePos.x > position.x && mousePos.x < position.x + width && mousePos.y > position.y && mousePos.y < position.y + height)
			{
				insideThis = true;
			}
			list->Input(insideThis, mousePos, event);
		}
	}
}

void Grid::SearchWidgets(std::string searchText)
{
	displayWidgets = {};
	for (size_t i = 0; i < widgets.size(); i++)
	{
		std::string type = typeid(*widgets[i]).name();
		type = type.substr(6);
		std::string widgetID = widgets[i]->GetID();
		std::transform(widgetID.begin(), widgetID.end(), widgetID.begin(), ::toupper);
		if ((widgetID.substr(0, searchText.length()) == searchText || searchText.length() == 0 || searchText == " ") && type != "Search" && type != "Row")
		{
			displayWidgets.push_back(widgets[i]);
		}
		else if (type == "Row")
		{
			widgets[i]->SearchWidgets(searchText);
			if (widgets[i]->GetDisplayWidgets()->size() > 0)
			{
				displayWidgets.push_back(widgets[i]);
			}
		}
		else if (type == "Search")
		{
			this->search = widgets[i];
		}
	}
	AutoAdjust();
}