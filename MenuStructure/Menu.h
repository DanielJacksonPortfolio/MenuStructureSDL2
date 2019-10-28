#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>

#include "UIConstants.h"

#include "Page.h"
#include "Grid.h"
#include "Row.h"
#include "Text.h"
#include "Button.h"
#include "Selector.h"
#include "Search.h"
#include "List.h"
#include "ScrollingList.h"
#include "Image.h"
#include "Widget.h"
#include "Slider.h"
#include "Font.h"
#include "Elements.h"

class Menu
{
private:
	SDL_Window * window = nullptr;
	SDL_Renderer * renderer = nullptr;
	int preferredFPS = 60;

	SDL_Point mousePos = { 0, 0 };
	Uint32 elapsedTime = 0, oldTime = 0 ;

	int fpsTarget = 1000;
	int elapsedTarget = 1000 / fpsTarget;

	std::unordered_map<std::string, std::function<void()>> voidFunctionMap = {};
	std::unordered_map<std::string, std::function<void(std::string string)>> stringFunctionMap = {};

	std::unordered_map<std::string, Widget*> widgetList = {};
	std::unordered_map<std::string, Font*> fonts = {};
	std::unordered_map<std::string, int*> settings = {};

	int brightness = 0;
	int contrast = 0;
	int buttonID = 0;

	Recipe* recipes = nullptr;
	Element* elements = nullptr;
	int* elementalUnlock = nullptr;
	int* recipeDicovered = nullptr;
	int numElements = -1;
	int numElementsUnlocked = -1;
	int numRecipes = -1;
	int numRecipesUnlocked = -1;

	bool wasPaused = false;
	
	std::string dateSaved = "N/A";
	std::string setSaveID = "1";

public:
	Menu(int argc, char * args[]);
	~Menu();
	bool InitSDL();
	void CloseSDL();
	bool Input();
	void Draw();
	bool Update();
	bool LoadContent();
	void Add(std::string containerID, std::string id, WidgetType widgetType, std::vector<std::pair<std::string, std::string>> valuePairs);
	void Null();
	void Quit();
	void LoadGame();
	void Settings();
	void PlayGame();
	void ButtonTest(std::string ID);
	void SetSave(std::string ID);
	void LoadSave();
	bool Back();
	void SpawnElement(std::string ID);
	void Resume();
	void HideAll();
	void ExitToMainMenu();
	void NewGame();
	void LoadRecipes();
	void LoadElements();
	void DoCombination();
	int GetRecipes(int item1, int item2, Recipe* recipes);
	void LoadSaveFile(std::string filePath = "resources/files/save.txt", bool metaDataOnly = false);
	void LoadData();
	void SaveGame();
	void UpdateElementList();
};