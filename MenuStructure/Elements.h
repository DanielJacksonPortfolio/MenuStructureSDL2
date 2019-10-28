#pragma once

#include <string>

class Recipe
{
private:
	int ID = 0, item1 = 0, item2 = 0, result = 0;
	bool discovered = false;
public:
	Recipe() {}
	Recipe(int item1, int item2, int result, int ID)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->result = result;
		this->ID = ID;
	}
	int GetItem(int itemNum = 3)
	{
		switch (itemNum)
		{
		case 0:
			return item1;
			break;
		case 1:
			return item2;
			break;
		case 2:
			return ID;
			break;
		default:
			return result;
			break;
		}
	}
	void SetItem(int val, int itemNum = 3)
	{
		switch (itemNum)
		{
		case 0:
			item1 = val;
			break;
		case 1:
			item2 = val;
			break;
		case 2:
			ID = val;
			break;
		default:
			result = val;
			break;
		}
	}
};

class Element
{
private:
	bool finalItem = false;
	std::string name = "";
	int ID = -1;
public:
	Element() {}
	Element(int ID, std::string name, bool finalItem)
	{
		this->ID = ID;
		this->name = name;
		this->finalItem = finalItem;
	}
	int GetID()
	{
		return ID;
	}
	std::string GetName()
	{
		return name;
	}
	std::string GetFinal()
	{
		if (finalItem)
			return "Final Item";
		else
			return "Not Final Item";
	}
	void SetID(int ID)
	{
		this->ID = ID;
	}
	void SetName(std::string name)
	{
		this->name = name;
	}
	void SetFinal(bool finalItem = false)
	{
		this->finalItem = finalItem;
	}
};