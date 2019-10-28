#include "Menu.h"

Menu::Menu(int argc, char * args[])
{
	if (InitSDL())
	{
		if (LoadContent())
		{
			SDL_GetTicks();
			oldTime = SDL_GetTicks();
			while (Update());
		}
	}

	CloseSDL();
}

Menu::~Menu()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	for (auto& item : widgetList)
	{
		delete item.second;
	}
	for (auto& item : fonts)
	{
		delete item.second;
	}
	for (auto& item : settings)
	{
		delete item.second;
	}
	widgetList.empty();
	fonts.empty();
	settings.empty();
}

bool Menu::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	if (TTF_Init() < 0)
	{
		std::cout << "SDL_TTF did not initialise. Error: " << SDL_GetError();
		return false;
	}
	window = SDL_CreateWindow("Menu Structure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer was not created. Error: " << SDL_GetError();
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Mixer WAV Initialization Error: " << SDL_GetError();
		return false;
	}
	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3) == 0)
	{
		std::cout << "Mixer OTHER Initialization Error: " << SDL_GetError();
		return false;
	}
	Mix_AllocateChannels(16);
	return true;
}

void Menu::CloseSDL()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Menu::LoadContent()
{
	//FONTS, FUNCTIONS, AND VARIABLES
	{
		voidFunctionMap["Back"] = [&, this]() { Back(); };
		voidFunctionMap["Load Game"] = [&, this]() { LoadGame(); };
		voidFunctionMap["Null"] = [&, this]() { Null(); };
		voidFunctionMap["Play Game"] = [&, this]() { PlayGame(); };
		voidFunctionMap["Quit"] = [&, this]() { Quit(); };
		voidFunctionMap["Settings"] = [&, this]() { Settings(); };
		voidFunctionMap["Do"] = [&, this]() { DoCombination(); };
		voidFunctionMap["Load"] = [&, this]() { LoadSave(); };
		voidFunctionMap["Resume"] = [&, this]() { Resume(); };
		voidFunctionMap["ExitToMainMenu"] = [&, this]() { ExitToMainMenu(); };

		stringFunctionMap["Set Save"] =		[&, this](std::string string) { SetSave(string); };
		stringFunctionMap["Null"] =				[&, this](std::string string) { ButtonTest(string); };
		stringFunctionMap["Spawn Element"] =	[&, this](std::string string) { SpawnElement(string); };

		settings["brightness"] = &brightness;
		settings["contrast"] = &contrast;

		//fonts["EMULOGIC25"]		= new Font(	"resources/fonts/emulogic.ttf", 25);
		fonts["MONOFONTO15"] = new Font("resources/fonts/monofonto.ttf", 15);
		fonts["MONOFONTO20"] = new Font("resources/fonts/monofonto.ttf", 20);
		fonts["MONOFONTO25"] = new Font("resources/fonts/monofonto.ttf", 25);
		fonts["MONOFONTO45"] = new Font("resources/fonts/monofonto.ttf", 45);
		fonts["MONOFONTO55"] = new Font("resources/fonts/monofonto.ttf", 55);
		//fonts["MONOFONTO60"] = new Font("resources/fonts/monofonto.ttf", 60);
		fonts["MONOFONTO80"] = new Font("resources/fonts/monofonto.ttf", 80);
		fonts["MONOFONTO100"] = new Font("resources/fonts/monofonto.ttf", 100);
		fonts["MONOFONTO200"] = new Font("resources/fonts/monofonto.ttf", 200);
		fonts["MONOFONTO300"] = new Font("resources/fonts/monofonto.ttf", 300);
		widgetList["SCREEN"] = new Widget();
	}
	//MAINMENU
	{
		Add("SCREEN", "MAINMENU", PAGE, { {"backgroundColor", "PURPLE2"} });
		Add("MAINMENU", "MENUBOX", STATIC_LIST, { {"width", "45"}, {"height", "45"},   {"backgroundColor", "PURPLE1"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"} });
		Add("MAINMENU", "TITLETEXT1", TEXT, { {"font", "MONOFONTO200"},  {"text", " LITTLE"}, {"positionX", "5"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "10"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("MAINMENU", "TITLETEXT2", TEXT, { {"font", "MONOFONTO200"},  {"text", "ALCHEMY"}, {"positionX", "95"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "10"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("MAINMENU", "TITLETEXT3", TEXT, { {"font", "MONOFONTO300"},  {"text", "3D"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "15"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("MAINMENU", "TITLEIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "175"}, {"height", "175"}, {"imagePath", "resources/textures/la2.png"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "10"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "300"}, {"rectH", "300"} });
		Add("MAINMENU", "SMALLPRINT", TEXT, { {"font", "MONOFONTO25"},  {"text", "Created by; Danny Jackson, Fergus Griggs, Niha Patel"}, {"positionX", "1"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "99"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"}, {"baseColor", "YELLOW1"} });
		Add("MENUBOX", "NEWGAMEBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Play Game"}, {"backgroundColor", "PURPLE2"} });
		Add("NEWGAMEBUTTON", "NEWGAMEBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "NEW GAME"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("NEWGAMEBUTTON", "NEWGAMEBUTTONIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/earth.png"}, {"positionX", "25"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		Add("NEWGAMEBUTTON", "NEWGAMEBUTTONIMAGE2", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/earth.png"}, {"positionX", "75"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		Add("MENUBOX", "LOADGAMEBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Load Game"}, {"backgroundColor", "PURPLE2"} });
		Add("LOADGAMEBUTTON", "LOADGAMEBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "LOAD GAME"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("LOADGAMEBUTTON", "LOADGAMEBUTTONIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/time.png"}, {"positionX", "25"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		Add("LOADGAMEBUTTON", "LOADGAMEBUTTONIMAGE2", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/time.png"}, {"positionX", "75"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		Add("MENUBOX", "SETTINGSBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Settings"}, {"backgroundColor", "PURPLE2"} });
		Add("SETTINGSBUTTON", "SETTINGSBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "SETTINGS"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("SETTINGSBUTTON", "SETTINGSBUTTONIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "60"}, {"height", "60"}, {"imagePath", "resources/textures/tool.png"}, {"positionX", "25"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "800"}, {"rectH", "800"} });
		Add("SETTINGSBUTTON", "SETTINGSBUTTONIMAGE2", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "60"}, {"height", "60"}, {"imagePath", "resources/textures/tool.png"}, {"positionX", "75"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "800"}, {"rectH", "800"} });
		Add("MENUBOX", "CREDITSBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"backgroundColor", "PURPLE2"} });
		Add("CREDITSBUTTON", "CREDITSBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "CREDITS"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("CREDITSBUTTON", "CREDITSBUTTONIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "60"}, {"height", "60"}, {"imagePath", "resources/textures/pencil.png"}, {"positionX", "25"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "800"}, {"rectH", "800"} });
		Add("CREDITSBUTTON", "CREDITSBUTTONIMAGE2", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "60"}, {"height", "60"}, {"imagePath", "resources/textures/pencil.png"}, {"positionX", "75"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "800"}, {"rectH", "800"} });
		Add("MENUBOX", "QUITBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Quit"}, {"backgroundColor", "PURPLE2"} });
		Add("QUITBUTTON", "QUITBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "QUIT"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("QUITBUTTON", "QUITBUTTONIMAGE1", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/fire.png"}, {"positionX", "25"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		Add("QUITBUTTON", "QUITBUTTONIMAGE2", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "65"}, {"height", "65"}, {"imagePath", "resources/textures/fire.png"}, {"positionX", "75"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "225"}, {"rectH", "225"} });
		widgetList["MENUBOX"]->AutoAdjust();
	}
	//PAUSEMENU
	{
		Add("SCREEN", "PAUSEMENUPAGE", PAGE, { {"backgroundColor", "YELLOW1"},{"width","50"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"} });
		Add("PAUSEMENUPAGE", "PAUSEMENU", PAGE, { {"backgroundColor", "PURPLE2"},{"width","98"},{"height","98"}, {"alignment","CENTRE" } });
		Add("PAUSEMENU", "PAUSESUBPAGE", PAGE, { {"backgroundColor", "PURPLE2"},{"height","20" },{"alignment","TOP"} });
		
		Add("PAUSESUBPAGE", "PAUSETEXT", TEXT, { {"font", "MONOFONTO200"},  {"text", " PAUSED "}, {"baseColor", "YELLOW1"}, {"alignment", "CENTRE"} });
		Add("PAUSEMENU", "PAUSELINE3", PAGE, { {"backgroundColor", "YELLOW1"},{"height","2" }, {"positionY", "20"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"} });
		
		Add("PAUSEMENU", "PAUSELIST", STATIC_LIST, { {"height", "78"},   {"backgroundColor", "PURPLE1"},{"positionY", "22"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"} });
		Add("PAUSELIST", "RESUMEGAMEBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Resume"}, {"backgroundColor", "PURPLE2"} });
		Add("RESUMEGAMEBUTTON", "RESUMEGAMEBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "RESUME GAME"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("PAUSELIST", "PAUSESETTINGSBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Settings"}, {"backgroundColor", "PURPLE2"} });
		Add("PAUSESETTINGSBUTTON", "PAUSESETTINGSBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "SETTINGS"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("PAUSELIST", "PAUSEQUITBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "ExitToMainMenu"}, {"backgroundColor", "PURPLE2"} });
		Add("PAUSEQUITBUTTON", "PAUSEQUITBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "EXIT TO MENU"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		Add("PAUSELIST", "EXITBUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"vFunctionID", "Quit"}, {"backgroundColor", "PURPLE2"} });
		Add("EXITBUTTON", "EXITBUTTONTEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "EXIT TO DESKTOP"}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		widgetList["PAUSELIST"]->AutoAdjust();
	}
	//EGRID
	{
		Add("SCREEN", "EGRID", GRID, { {"width", "25"}, {"alignment", "RIGHT"}, {"backgroundColor", "PURPLE1"}, {"rowCount", "4"} });
		NewGame();


	}
	//LOAD MENU
	{
		Add("SCREEN", "LOADPAGE", PAGE, { {"backgroundColor", "YELLOW1"} });
		Add("LOADPAGE", "LOADPAGEINNER", PAGE, { {"backgroundColor", "PURPLE2"},{"width","98"},{"alignment","CENTRE"},{"height","97"} });

		Add("LOADPAGEINNER", "LOADBOX", SCROLLING_LIST, { {"width", "36"}, {"height","85"}, {"backgroundColor", "PURPLE1"}, {"positionX", "13"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "100"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"} });
		for (int i = 0; i < 10; i++)
		{
			Add("LOADBOX", "LOAD " + std::to_string(i + 1) + " BUTTON", BUTTON, { {"width", "95"}, {"height", "15"},   {"sFunctionID", "Set Save"},{"functionMode","STRING"},  {"backgroundColor", "PURPLE2"} });
			Add("LOAD " + std::to_string(i + 1) + " BUTTON", "LOAD " + std::to_string(i + 1) + " TEXT", TEXT, { {"font", "MONOFONTO45"},  {"text", "SAVE " + std::to_string(i + 1)}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		}

		widgetList["LOADBOX"]->SetAllWidgets();
		Add("LOADPAGEINNER", "SAVETEXT", TEXT, { {"containerID","LOADBOX"},{"font", "MONOFONTO100"},  {"text", " SAVES "}, {"baseColor", "YELLOW1"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "-3"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"} });

		Add("LOADPAGEINNER", "LOADLINE1", PAGE, { {"backgroundColor", "YELLOW1"},{"width", "2"}, {"positionX", "11"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"} });
		Add("LOADPAGEINNER", "LOADLINE2", PAGE, { {"backgroundColor", "YELLOW1"},{"width", "2"}, {"positionX", "49"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"} });
		Add("LOADPAGEINNER", "LOADLINE3", PAGE, { {"backgroundColor", "YELLOW1"},{"width", "89"}, {"height","2"}, {"positionX", "12"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "15"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"} });
		
		Add("LOADPAGEINNER", "LOADSUBPAGE1", PAGE, { {"colorMode","TRANSPARENT"},{"backgroundColor", "PURPLE2"},{"width", "49"},{"alignment","RIGHT"} });
		Add("LOADSUBPAGE1", "LOADTEXT", TEXT, { {"font", "MONOFONTO100"},  {"text", " LOAD GAME"}, {"alignment", "TOP"}, {"baseColor", "YELLOW1"} });

		Add("LOADSUBPAGE1", "LOADSUBPAGE2", PAGE, { {"backgroundColor","PURPLE1"}, {"height", "85"},{"alignment","BOTTOM"} });
		Add("LOADSUBPAGE2", "LOADBUTTON", BUTTON, { {"width", "50"}, {"height", "15"},   {"vFunctionID", "Load"}, {"backgroundColor", "YELLOW1"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "95"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"} });
		Add("LOADBUTTON", "LOADBUTTONTEXT", TEXT, { {"font", "MONOFONTO80"},  {"text", "LOAD "}, {"alignment", "CENTRE"}, {"baseColor", "PURPLE2"}, {"hoverColor", "PURPLE2"} });
		
		Add("LOADSUBPAGE2", "SELECTEDSAVETEXT", TEXT, { {"font", "MONOFONTO55"},  {"text", "SELECTED SAVE: "},		{"positionX", "5"},	{"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "4"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "SAVEDATETEXT",		TEXT, { {"font", "MONOFONTO55"},  {"text", "DATE SAVED: "},			{"positionX", "5"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "14"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "EUNLOCKSTEXT",		TEXT, { {"font", "MONOFONTO55"},  {"text", "ELEMENTS UNLOCKED: "},	{"positionX", "5"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "24"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "RUNLOCKSTEXT",		TEXT, { {"font", "MONOFONTO55"},  {"text", "RECIPES UNLOCKED: "},		{"positionX", "5"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "34"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		
		Add("LOADSUBPAGE2", "SELECTEDSAVEDATA", TEXT, { {"font", "MONOFONTO55"},  {"text", setSaveID},						{"positionX", "95"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "4"},  {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "SAVEDATEDATA",	TEXT, { {"font", "MONOFONTO55"},  {"text", dateSaved},							{"positionX", "95"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "14"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "EUNLOCKSDATA", TEXT, { {"font", "MONOFONTO55"}, 	{"text", "0/" + std::to_string(numElements)},	{"positionX", "95"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "24"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		Add("LOADSUBPAGE2", "RUNLOCKSDATA", TEXT, { {"font", "MONOFONTO55"},  {"text", "0/" + std::to_string(numRecipes) },		{"positionX", "95"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "34"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"}, {"baseColor", "YELLOW1"} });
		
		Add("LOADPAGEINNER", "BACKBUTTON2", BUTTON, { {"width", "9"}, {"height", "9"},   {"colorMode","TRANSPARENT"}, {"vFunctionID", "Back"},{"positionX", "1"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "2"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"} });
		Add("BACKBUTTON2", "BACKBUTTON2IMAGE", IMAGE, { {"imagePath", "resources/textures/Back.png"}, {"imageLoadMode", "EXACT"}, {"rectW", "400"}, {"rectH", "225"} });
	}
	//SETTINGS
	{
		Add("SCREEN", "SETTINGSPAGE", PAGE, { {"backgroundColor", "PURPLE2"} });
		Add("SETTINGSPAGE", "SETTINGSTEXT", TEXT, { {"font", "MONOFONTO100"},  {"text", " SETTINGS "}, {"alignment", "TOP"}, {"baseColor", "YELLOW1"} });
		
		Add("SETTINGSPAGE", "SETTINGSBOX", PAGE, { {"width", "80"}, {"height", "80"},   {"backgroundColor", "PURPLE1"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "95"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"} });
		
		Add("SETTINGSBOX", "SLIDER1", SLIDER, { {"width", "65"}, {"height", "15"}, {"positionX", "90"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "0"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"},   {"colorMode", "TRANSPARENT"} , {"barColor", "PURPLE2"}, {"knobColor", "YELLOW1"}, {"value", "brightness"} });
		Add("SLIDER1", "SLIDER1TEXT", TEXT, { {"font", "MONOFONTO25"},  {"text", std::to_string(brightness)}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionX", "102"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"baseColor", "YELLOW1"} });									 
		Add("SETTINGSBOX", "BRIGHTNESSTEXT", TEXT, { {"containerID","SLIDER1"}, {"positionX", "-5"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "46"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"font", "MONOFONTO45"},  {"text", "BRIGHTNESS"}, {"baseColor", "YELLOW1"} });
		
		Add("SETTINGSBOX", "SLIDER2", SLIDER, { {"width", "65"}, {"height", "15"}, {"positionX", "90"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "15"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"},   {"colorMode", "TRANSPARENT"} , {"barColor", "PURPLE2"}, {"knobColor", "YELLOW1"}, {"value", "contrast"} });
		Add("SLIDER2", "SLIDER2TEXT", TEXT, { {"font", "MONOFONTO25"},  {"text", std::to_string(contrast)}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionX", "102"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"baseColor", "YELLOW1"} });									 
		Add("SETTINGSBOX", "CONTRASTTEXT", TEXT, { {"containerID","SLIDER2"}, {"positionX", "-5"}, {"positionModeX", "POSITION_PERCENTAGE_RIGHT"}, {"positionY", "46"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"font", "MONOFONTO45"},  {"text", "CONTRAST"}, {"baseColor", "YELLOW1"} });
		
		Add("SETTINGSBOX", "RESOLUTIONSELECTOR", SELECTOR, { {"width", "50"}, {"height", "20"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "35"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"},   {"colorMode", "TRANSPARENT"}, {"backgroundColor", "PURPLE1"} });
		Add("RESOLUTIONSELECTOR", "640x480",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", " 640x480 "}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "1280x720",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "1280x720 "}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "1920x1080",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "1920x1080"}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "2560x1440",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "2560x1440"}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "2048x1080",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "2048x1080"}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "3840x2160",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "3840x2160"}, {"baseColor", "YELLOW1"} });
		Add("RESOLUTIONSELECTOR", "7680x4320",	TEXT, { {"alignment","CENTRE"},	{"font", "MONOFONTO100"}, {"text", "7680x4320"}, {"baseColor", "YELLOW1"} });

		Add("SETTINGSBOX", "RESOLUTIONTEXT", TEXT, { {"containerID","RESOLUTIONSELECTOR"}, {"positionX", "50"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionModeY", "POSITION_PERCENTAGE_RIGHT"}, {"font", "MONOFONTO45"},  {"text", "RESOLUTION "}, {"baseColor", "YELLOW1"} });

		Add("RESOLUTIONSELECTORLEFTBUTTON", "RESOLUTIONSELECTORLEFTIMAGE", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "70"}, {"height", "70"},   {"imagePath", "resources/textures/left.png"}, {"alignment", "CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "86"}, {"rectH", "194"} });
		Add("RESOLUTIONSELECTORRIGHTBUTTON", "RESOLUTIONSELECTORRIGHTIMAGE", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "70"}, {"height", "70"},   {"imagePath", "resources/textures/right.png"}, {"alignment", "CENTRE"}, {"imageLoadMode", "EXACT"}, {"rectW", "86"}, {"rectH", "194"} });

		widgetList["RESOLUTIONSELECTOR"]->AutoAdjust();
		Add("SETTINGSPAGE", "BACKBUTTON3", BUTTON, { {"containerID","SCREEN"}, {"width", "9"}, {"height", "9"},   {"colorMode","TRANSPARENT"}, {"vFunctionID", "Back"},{"positionX", "1"}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionY", "2"}, {"positionModeY", "POSITION_PERCENTAGE_LEFT"} });
		Add("BACKBUTTON3", "BACKBUTTON3IMAGE", IMAGE, { {"imagePath", "resources/textures/Back.png"}, {"imageLoadMode", "EXACT"}, {"rectW", "400"}, {"rectH", "225"} });
	}

	widgetList["MAINMENU"]->SetShow(true);
	widgetList["PAUSEMENUPAGE"]->SetShow(false);
	widgetList["SETTINGSPAGE"]->SetShow(false);
	widgetList["LOADPAGE"]->SetShow(false);
	widgetList["EGRID"]->SetShow(false);

	return true;
}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(renderer, 92, 148, 252, 255);
	SDL_RenderClear(renderer);
	widgetList["SCREEN"]->Draw(renderer);

	SDL_RenderPresent(renderer);
}


void Menu::Add(std::string parentID, std::string id, WidgetType widgetType, std::vector<std::pair<std::string, std::string>> valuePairs)
{
	std::string sFunctionID = "Null", vFunctionID = "Null", imagePath = "", text = "NULL", fontPath = "", containerID = "NULL", searchContainerID = "NULL";
	int width = 100, height = 100, fontSize = 10, rectW = 100, rectH = 100, rectX = 0, rectY = 0, knobWidth = 20, knobHeight = 60, numberOfPoints = 100, maxLength = 20, rowCount = 3;
	int* value = nullptr;
	float positionX = 0.0f, positionY = 0.0f;
	DimensionType widthMode = DIMENSION_PERCENTAGE, heightMode = DIMENSION_PERCENTAGE;
	AlignmentType alignment = ALIGNMENT_ABSOLUTE, internalAlignment = ALIGNMENT_ABSOLUTE;
	PositionType positionModeX = POSITION_ABSOLUTE, positionModeY = POSITION_ABSOLUTE;
	Color backgroundColor = { 255, 255, 255 }, barColor = { 255, 255, 255 }, knobColor = { 255, 255, 255 }, baseColor = { 255, 255, 255 }, hoverColor = { 255, 255, 255 };
	ColorMode colorMode = FILLED;
	TextRenderModes textRenderMode = BLENDED;
	TextDisplayModes textDisplayMode = DISABLE_RESTRAINTS;
	ImageLoadModes imageLoadMode = EXACT;
	ScrollMode scrollMode = SMOOTH;
	FunctionModes functionMode = VOID;
	RowModes rowMode = WIDGET;
	Font* font = nullptr;

	for (size_t i = 0; i < valuePairs.size(); i++)
	{
		if (valuePairs[i].first == "imagePath")
		{
			imagePath = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "text")
		{
			text = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "containerID")
		{
			containerID = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "searchContainerID")
		{
			searchContainerID = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "vFunctionID")
		{
			vFunctionID = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "sFunctionID")
		{
			sFunctionID = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "fontPath")
		{
			fontPath = valuePairs[i].second;
		}
		else if (valuePairs[i].first == "width")
		{
			width = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "height")
		{
			height = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "rowCount")
		{
			rowCount = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "knobWidth")
		{
			knobWidth = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "knobHeight")
		{
			knobHeight = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "numberOfPoints")
		{
			numberOfPoints = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "maxLength")
		{
			maxLength = stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "rectW")
		{
			rectW = stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "rectH")
		{
			rectH = stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "rectX")
		{
			rectX = stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "rectY")
		{
			rectY = stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "fontSize")
		{
			fontSize = std::stoi(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "positionX")
		{
			positionX = stof(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "positionY")
		{
			positionY = stof(valuePairs[i].second);
		}
		else if (valuePairs[i].first == "backgroundColor")
		{
			backgroundColor.r = Colors[valuePairs[i].second][0];
			backgroundColor.g = Colors[valuePairs[i].second][1];
			backgroundColor.b = Colors[valuePairs[i].second][2];
		}	
		else if (valuePairs[i].first == "knobColor")
		{
			knobColor.r = Colors[valuePairs[i].second][0];
			knobColor.g = Colors[valuePairs[i].second][1];
			knobColor.b = Colors[valuePairs[i].second][2];
		}	
		else if (valuePairs[i].first == "barColor")
		{
			barColor.r = Colors[valuePairs[i].second][0];
			barColor.g = Colors[valuePairs[i].second][1];
			barColor.b = Colors[valuePairs[i].second][2];
		}		
		else if (valuePairs[i].first == "baseColor")
		{
			baseColor.r = Colors[valuePairs[i].second][0];
			baseColor.g = Colors[valuePairs[i].second][1];
			baseColor.b = Colors[valuePairs[i].second][2];
		}		
		else if (valuePairs[i].first == "hoverColor")
		{
			hoverColor.r = Colors[valuePairs[i].second][0];
			hoverColor.g = Colors[valuePairs[i].second][1];
			hoverColor.b = Colors[valuePairs[i].second][2];
		}
		else if (valuePairs[i].first == "colorMode")
		{
			colorMode = ColorModeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "textRenderMode")
		{
			textRenderMode = TextRenderModesMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "textDisplayMode")
		{
			textDisplayMode = TextDisplayModesMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "widthMode")
		{
			widthMode = DimensionTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "heightMode")
		{
			heightMode = DimensionTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "functionMode")
		{
			functionMode = FunctionModesMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "alignment")
		{
			alignment = AlignmentTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "internalAlignment")
		{
			internalAlignment = AlignmentTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "positionModeX")
		{
			positionModeX = PositionTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "positionModeY")
		{
			positionModeY = PositionTypeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "imageLoadMode")
		{
			imageLoadMode = ImageLoadModesMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "scrollMode")
		{
			scrollMode = ScrollModeMap[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "font")
		{
			font = fonts[valuePairs[i].second];
		}
		else if (valuePairs[i].first == "value")
		{
			value = settings[valuePairs[i].second];
		}
	}

	if (containerID == "NULL")
	{
		containerID = parentID;
	}
	if (searchContainerID == "NULL")
	{
		searchContainerID = parentID;
	}

	std::function<void()> vFunction = voidFunctionMap[vFunctionID];
	std::function<void(std::string)> sFunction = stringFunctionMap[sFunctionID];
	Widget* container = widgetList[containerID];
	Widget* searchContainer = widgetList[searchContainerID];
	Vec2 position = { positionX, positionY };
	std::string ID = id;

	switch (widgetType)
	{
	case PAGE:
		widgetList[parentID]->AddPage(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, backgroundColor, colorMode); break;	
	case ROW:
		widgetList[parentID]->AddRow(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, backgroundColor, colorMode); break;	
	case STATIC_LIST:
		widgetList[parentID]->AddList(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, backgroundColor, colorMode); break;
	case SCROLLING_LIST:
		widgetList[parentID]->AddScrollingList(	&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, backgroundColor, colorMode, scrollMode); break;
	case GRID:
		widgetList[parentID]->AddGrid(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, backgroundColor, colorMode, scrollMode, rowCount, rowMode); break;
	case BUTTON:
		widgetList[parentID]->AddButton(		&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, vFunction,sFunction,functionMode, backgroundColor, colorMode); break;
	case TEXT:													 
		widgetList[parentID]->AddText(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, text, font, fontPath, fontSize, renderer, textDisplayMode, baseColor, hoverColor, textRenderMode); break;
	case IMAGE:
		widgetList[parentID]->AddImage(			&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, rectW, rectH, rectX, rectY, imagePath, renderer, imageLoadMode); break;
	case SLIDER:
		widgetList[parentID]->AddSlider(		&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, knobWidth, knobHeight, value, numberOfPoints, backgroundColor, barColor, knobColor, colorMode); break;
	case SEARCH:
		widgetList[parentID]->AddSearch(		&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, maxLength, searchContainer, backgroundColor, colorMode); break;
	case SELECTOR:
		widgetList[parentID]->AddSelector(		&widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, sFunction, backgroundColor, colorMode); break;
	}
}

bool Menu::Update()
{
	elapsedTime = SDL_GetTicks() - oldTime;
	if (elapsedTime < static_cast<Uint32>(elapsedTarget))
	{
		SDL_Delay(elapsedTarget - elapsedTime);
		elapsedTime = elapsedTarget - elapsedTime;
	}
	oldTime = SDL_GetTicks();

	if (static_cast<int>(elapsedTime) < 1000 / preferredFPS)
		SDL_Delay(1000 / preferredFPS - elapsedTime);

	bool const running = Input();

	widgetList["SCREEN"]->Update();
	widgetList["RESOLUTIONTEXT"]->UpdateColor({static_cast<int>(Colors["YELLOW1"][0] * (brightness * 0.01f)), static_cast<int>(Colors["YELLOW1"][1] * (brightness * 0.01f)), static_cast<int>(Colors["YELLOW1"][2] * (brightness * 0.01f)) }, BASE);

	Draw();
	return running;
}

void Menu::HideAll()
{
	widgetList["MAINMENU"]->SetShow(false);
	widgetList["PAUSEMENUPAGE"]->SetShow(false);
	widgetList["SETTINGSPAGE"]->SetShow(false);
	widgetList["LOADPAGE"]->SetShow(false);
	widgetList["EGRID"]->SetShow(false);
}
void Menu::ExitToMainMenu()
{
	HideAll();
	wasPaused = false;
	widgetList["MAINMENU"]->SetShow(true);
}

bool Menu::Back()
{
	if (widgetList["MAINMENU"]->GetShow())
	{
		return false;
	}
	else if (widgetList["SETTINGSPAGE"]->GetShow())
	{
		HideAll();
		if (wasPaused)
		{
			widgetList["SETTINGSPAGE"]->SetShow(true);
		}
		else
		{
			widgetList["MAINMENU"]->SetShow(true);
			wasPaused = false;
		}
	}
	else if (widgetList["PAUSEMENUPAGE"]->GetShow())
	{
		HideAll();
		widgetList["EGRID"]->SetShow(true);
		wasPaused = false;
	}
	else if (widgetList["EGRID"]->GetShow())
	{
		HideAll();
		wasPaused = true;
		widgetList["PAUSEMENUPAGE"]->SetShow(true);
	}
	else if (widgetList["LOADPAGE"]->GetShow())
	{
		ExitToMainMenu();
	}
	return true;
}

bool Menu::Input()
{
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		//if (!Back())
		return false;
		break;
	case SDL_KEYDOWN:
		 // switch (event.key.keysym.sym)
		 // {
		 // }
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (!Back())
				return false;
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
		}
		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0)
		{
		}
		if (event.wheel.y < 0)
		{
		}
		break;
	}

	widgetList["SCREEN"]->Input(true, mousePos, event);
	return true;

}

void Widget::AddPage(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type == "Page" || type == "Widget")
	{
		this->widgets.push_back(new Page(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}

void Widget::AddList(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type == "Page" || type == "Widget")
	{
		this->widgets.push_back(new List(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}

void Widget::AddScrollingList(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, ScrollMode scrollMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type == "Page" || type == "Widget")
	{
		this->widgets.push_back(new ScrollingList(widgetList, ID, container, scrollMode, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}
 
void Widget::AddText(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::string textString, Font* font, std::string fontPath, int fontSize, SDL_Renderer* renderer, TextDisplayModes displayMode, Color baseColor, Color hoverColor, TextRenderModes renderMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Text" && type != "Image")
	{
		this->widgets.push_back(new Text(widgetList, ID, container, textString, font, fontPath, fontSize, width, height, renderer, displayMode, widthMode, heightMode, alignment, position, positionModeX, positionModeY, baseColor, hoverColor, renderMode));
	}
}

void Widget::AddImage(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int rectW, int rectH, int rectX, int rectY, std::string imageLocation, SDL_Renderer* renderer, ImageLoadModes imageLoadMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Text" && type != "Image")
	{
		this->widgets.push_back(new Image(widgetList, ID, container, width, height, rectW, rectH, rectX, rectY, imageLocation, renderer, widthMode, heightMode, alignment, position, positionModeX, positionModeY, imageLoadMode));
	}
}

void Widget::AddButton(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::function<void()> vFunction, std::function<void(std::string)> sFunction, FunctionModes functionMode, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Button" && type != "Text" && type != "Image")
	{
		this->widgets.push_back(new Button(widgetList, ID, container, width, height, vFunction,sFunction,functionMode, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}

void Widget::AddSelector(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, std::function<void(std::string)> function, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Button" && type != "Text" && type != "Image")
	{
		this->widgets.push_back(new Selector(widgetList, ID, container, width, height, function, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}


void Widget::AddRow(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type == "List" || type == "ScrollingList")
	{
		this->widgets.push_back(new Row(widgetList, ID, container, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}


void Widget::AddGrid(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, Color color, ColorMode colorMode, ScrollMode scrollMode, int rowCount, RowModes rowMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type == "Page" || type == "Widget")
	{
		this->widgets.push_back(new Grid(widgetList, ID, container, scrollMode, width, height, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode, rowCount, rowMode));
	}
}

void Widget::AddSearch(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int maxLength, Widget* searchContainer, Color color, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Button" && type != "Slider" && type != "Search" && type != "Text" && type != "Image")
	{
		this->widgets.push_back(new Search(widgetList, ID, container, maxLength, width, height, searchContainer, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, colorMode));
	}
}

void Widget::AddSlider(std::unordered_map<std::string, Widget*>* widgetList, std::string ID, Widget* container, int width, int height, DimensionType widthMode, DimensionType heightMode, AlignmentType alignment, Vec2 position, PositionType positionModeX, PositionType positionModeY, int knobWidth, int knobHeight, int* value, int numberOfPoints, Color color, Color color2, Color color3, ColorMode colorMode)
{
	std::string type = typeid(*this).name();
	type = type.substr(6);
	if (type != "Button" && type != "Search" && type != "Slider" && type != "Text" && type != "Image")
	{
		this->widgets.push_back(new	Slider( widgetList, ID, container, width, height, knobWidth, knobHeight, value, numberOfPoints, widthMode, heightMode, alignment, position, positionModeX, positionModeY, color, color2, color3, colorMode));
	}
}

void Menu::Null()
{
	std::cout << "Button Pressed" << std::endl;
}

void Menu::Quit()
{
	CloseSDL();
	exit(0);
}
void Menu::Settings()
{
	widgetList["MAINMENU"]->SetShow(false);
	widgetList["SETTINGSPAGE"]->SetShow(true);
	widgetList["EGRID"]->SetShow(false);
}
void Menu::Resume()
{
	widgetList["PAUSEPAGE"]->SetShow(false);
	widgetList["EGRID"]->SetShow(true);
}
void Menu::PlayGame()
{
	widgetList["MAINMENU"]->SetShow(false);
	widgetList["LOADPAGE"]->SetShow(false);
	widgetList["EGRID"]->SetShow(true);
	LoadSaveFile("resources/files/defaultSave.txt");
}

void Menu::LoadGame()
{
	widgetList["MAINMENU"]->SetShow(false);
	widgetList["LOADPAGE"]->SetShow(true);
	SetSave("SAVE 1 BUTTON");
}
void Menu::ButtonTest(std::string ID)
{
	std::cout << ID+" ACTIVE" << std::endl;
}

void Menu::SetSave(std::string ID)
{
	ID = ID.substr(5);
	ID = ID.substr(0, ID.find(" "));
	setSaveID = ID;
	LoadSaveFile("resources/files/save" + setSaveID + ".txt",true);
	widgetList["SELECTEDSAVEDATA"]->UpdateText(setSaveID);
	widgetList["SAVEDATEDATA"]->UpdateText(dateSaved);
	widgetList["EUNLOCKSDATA"]->UpdateText(std::to_string(numElementsUnlocked) + "/" + std::to_string(numElements));
	widgetList["EUNLOCKSDATA"]->UpdateColor({ static_cast<int>(255 * (1.0f - (static_cast<float>(numElementsUnlocked) / static_cast<float>(numElements)))), static_cast<int>(255 * (static_cast<float>(numElementsUnlocked) / static_cast<float>(numElements))), 0 }, BASE);
	widgetList["RUNLOCKSDATA"]->UpdateText(std::to_string(numRecipesUnlocked) + "/" + std::to_string(numRecipes));
	widgetList["RUNLOCKSDATA"]->UpdateColor({ static_cast<int>(255 * (1.0f - (static_cast<float>(numRecipesUnlocked) / static_cast<float>(numRecipes)))), static_cast<int>(255 * (static_cast<float>(numRecipesUnlocked) / static_cast<float>(numRecipes))), 0 }, BASE);	
}

void Menu::LoadSave()
{
	LoadSaveFile("resources/files/save" + setSaveID + ".txt");
	widgetList["MAINMENU"]->SetShow(false);
	widgetList["LOADPAGE"]->SetShow(false);
	widgetList["EGRID"]->SetShow(true);
}


void Menu::SpawnElement(std::string ID)
{
	ID = ID.substr(0, ID.find(" BUTTON"));
	std::cout << "Spawning " + ID << std::endl;
}

void Menu::LoadRecipes()
{
	std::ifstream recipeList;
	recipeList.open("resources/files/recipes.txt");
	if (recipeList.is_open())
	{
		int numResults;
		recipeList >> numResults;
		recipeList >> numRecipes;
		recipes = new Recipe[numRecipes];
		int count = 0;
		for (int i = 0; i < numResults; i++)
		{
			int result, numSubRecipes;
			recipeList >> result;
			recipeList >> numSubRecipes;
			for (int j = 0; j < numSubRecipes; j++)
			{
				int item1, item2;
				recipeList >> item1;
				recipeList >> item2;

				recipes[count].SetItem(item1, 0);
				recipes[count].SetItem(item2, 1);
				recipes[count].SetItem(count, 2);
				recipes[count].SetItem(result, 3);
				count++;
			}
		}
	}
	else
	{
		std::cout << "Error Loading Recipes" << std::endl;
	}
	recipeList.close();
}
void Menu::LoadElements()
{
	std::ifstream elementList;
	elementList.open("resources/files/elements.txt");
	if (elementList.is_open())
	{
		elementList >> numElements;
		elements = new Element[numElements];
		for (int i = 0; i < numElements; i++)
		{
			int buffer, finalItem;
			std::string name;
			elementList >> buffer;
			elementList >> name;
			std::replace(name.begin(), name.end(), '_', ' ');
			elementList >> finalItem;
			elements[i].SetID(i);
			elements[i].SetName(name);
			elements[i].SetFinal(finalItem);
		}
	}
	else
	{
		std::cout << "Error Loading Elements" << std::endl;
	}
	elementList.close();
}

void Menu::LoadSaveFile(std::string filePath,bool metaDataOnly)
{
	std::ifstream saveFile;
	saveFile.open(filePath);

	if (saveFile.is_open())
	{
		std::getline(saveFile, dateSaved);
		saveFile >> numElementsUnlocked;
		saveFile >> numRecipesUnlocked;
		if (!metaDataOnly)
		{
			elementalUnlock = new int[numElements];
			int state = 0;
			for (int i = 0; i < numElements; i++)
			{
				saveFile >> state;
				elementalUnlock[i] = state;
			}
			recipeDicovered = new int[numRecipes];
			for (int i = 0; i < numRecipes; i++)
			{
				saveFile >> state;
				recipeDicovered[i] = state;
			}
		}
	}
	else
	{
		std::cout << "Error Loading" << std::endl;
	}
	saveFile.close();

	UpdateElementList();
}

void Menu::UpdateElementList()
{
	widgetList["EGRID"]->ClearWidgets();
	Add("EGRID", "ESEARCH", SEARCH, { {"width", "90"},{"heightMode","DIMENSION_ABSOLUTE"},  {"backgroundColor", "PURPLE2"} });
	Add("ESEARCH", "ESEARCHTEXT", TEXT, { {"font", "MONOFONTO25"},  {"maxLength", "25"}, {"text", "Search..."}, {"positionModeX", "POSITION_PERCENTAGE_LEFT"}, {"positionX", "5"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"baseColor", "YELLOW1"} });
	Add("ESEARCH", "ESEARCHIMAGE", IMAGE, { {"widthMode", "DIMENSION_ABSOLUTE"}, {"heightMode", "DIMENSION_ABSOLUTE"}, {"width", "30"}, {"height", "30"}, {"imagePath", "resources/textures/search.png"}, {"positionX", "90"}, {"positionModeX", "POSITION_PERCENTAGE_CENTRE"}, {"positionY", "50"}, {"positionModeY", "POSITION_PERCENTAGE_CENTRE"}, {"imageLoadMode", "ORIGINAL"} });
	for (int i = 0; i < numElements; i++)
	{
		if (elementalUnlock[i] == 1)
		{
			Add("EGRID", elements[i].GetName() + " BUTTON", BUTTON, { {"width", "22"},{"heightMode","DIMENSION_ABSOLUTE"},  {"backgroundColor", "PURPLE2"},   {"sFunctionID", "Spawn Element"},{"functionMode","STRING"} });
			Add(elements[i].GetName() + " BUTTON", elements[i].GetName() + " TEXT", TEXT, { {"font", "MONOFONTO15"},  {"text",elements[i].GetName()}, {"alignment", "CENTRE"}, {"baseColor", "YELLOW1"} });
		}
	}
	widgetList["EGRID"]->SearchWidgets("");
}

void Menu::SaveGame()
{
	std::ofstream saveFile;
	saveFile.open("resources/files/save.txt");
	if (saveFile.is_open())
	{
		for (int i = 0; i < numElements; i++)
		{
			saveFile << elementalUnlock[i];
			saveFile << std::endl;
		}

		for (int i = 0; i < numRecipes; i++)
		{
			saveFile << recipeDicovered[i];
			saveFile << std::endl;
		}
	}
	else
	{
		std::cout << "Error Saving" << std::endl;
	}
	saveFile.close();
}

void Menu::LoadData()
{
	LoadRecipes();
	LoadElements();
	LoadSaveFile("resources/files/defaultSave.txt");
}

void Menu::NewGame()
{
	LoadData();
	srand(time(0));
};

void Menu::DoCombination()
{
	int item1, item2;
	std::cout << "Item 1: ";
	std::cin >> item1;
	std::cout << "Item 2: ";
	std::cin >> item2;

	if (elementalUnlock[item1] == 1 && elementalUnlock[item2] == 1)
	{
		int recipeID = GetRecipes(item1, item2, recipes);
		if (recipeDicovered[recipeID] == 0)
		{
			recipeDicovered[recipeID] = 1;
			std::cout << elements[recipes[recipeID].GetItem(0)].GetName() << " + " << elements[recipes[recipeID].GetItem(1)].GetName() << " = " << elements[recipes[recipeID].GetItem()].GetName() << std::endl;
			if (elementalUnlock[elements[recipes[recipeID].GetItem()].GetID()] == 0)
			{
				elementalUnlock[elements[recipes[recipeID].GetItem()].GetID()] = 1;
				UpdateElementList();
			}
		}
		else if (recipeDicovered[recipeID] == 1)
		{
			std::cout << "That has already been discovered" << std::endl;
		}
		else if (recipeID == -1)
		{
			std::cout << "That doesn't seem to do anything" << std::endl;
		}
	}
	else
	{
		std::cout << "You are meddling with concepts you dont understand" << std::endl;
	}

}

int Menu::GetRecipes(int item1, int item2, Recipe* recipes)
{
	for (int i = 0; i < numRecipes; i++)
	{
		if (recipes[i].GetItem(0) == item1)
		{
			if (recipes[i].GetItem(1) == item2)
			{
				return i;
			}
		}
		else if (recipes[i].GetItem(1) == item1)
		{
			if (recipes[i].GetItem(0) == item2)
			{
				return i;
			}
		}
	}
	return -1;
}