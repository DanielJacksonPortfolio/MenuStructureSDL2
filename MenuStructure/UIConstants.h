#pragma once

#define WINDOW_WIDTH 1728
#define WINDOW_HEIGHT 972

#include <vector>
#include <unordered_map>
#include <array>
#include <sstream>
#include <SDL.h>

struct Vec2;
struct Color;
struct Rect;

struct Rect
{
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	Rect(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

struct Vec2
{
	float x = 0;
	float y = 0;
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Color
{
	int r = 0;
	int g = 0;
	int b = 0;
	Color(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

enum TextRenderModes {SOLID, SHADED, BLENDED, WRAPPED};
enum TextDisplayModes {CUTOFF, DIMENSION_BASED, DISABLE_RESTRAINTS, CONTAINER, TEXT_EXACT};
enum DimensionType {DIMENSION_ABSOLUTE, DIMENSION_PERCENTAGE};
enum ColorMode {TRANSPARENT, FILLED};
enum DrawMode {HOVER, BASE};
enum ScrollMode {LIST, SMOOTH};
enum WidgetType {PAGE, BUTTON, TEXT, IMAGE, STATIC_LIST, SCROLLING_LIST, NAVBAR, SLIDER, SEARCH, ROW, GRID, SELECTOR};
enum AlignmentType {ALIGNMENT_ABSOLUTE, TOP_LEFT, TOP_RIGHT, CENTRE, TOP, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM, LEFT, RIGHT};
enum PositionType {POSITION_ABSOLUTE, POSITION_PERCENTAGE_LEFT, POSITION_PERCENTAGE_RIGHT, POSITION_PERCENTAGE_CENTRE};
enum ImageLoadModes {STRETCH, ORIGINAL, EXACT};
enum RowModes {WIDGET, PIXEL, PERCENTAGE};
enum FunctionModes {VOID, STRING, INT};

static std::unordered_map<std::string, TextRenderModes>		TextRenderModesMap = 	{ {"SOLID", SOLID}, {"SHADED", SHADED}, {"BLENDED", BLENDED}, {"WRAPPED", WRAPPED } };
static std::unordered_map<std::string, ImageLoadModes>		ImageLoadModesMap = 	{ {"STRETCH", STRETCH}, {"ORIGINAL", ORIGINAL}, {"EXACT", EXACT}};
static std::unordered_map<std::string, TextDisplayModes>	TextDisplayModesMap = 	{ {"CUTOFF", CUTOFF}, {"DIMENSION_BASED", DIMENSION_BASED}, {"DISABLE_RESTRAINTS", DISABLE_RESTRAINTS}, {"CONTAINER", CONTAINER }, {"TEXT_EXACT", TEXT_EXACT } };
static std::unordered_map<std::string, DimensionType>		DimensionTypeMap = 		{ {"DIMENSION_ABSOLUTE", DIMENSION_ABSOLUTE}, {"DIMENSION_PERCENTAGE", DIMENSION_PERCENTAGE}};
static std::unordered_map<std::string, ColorMode>			ColorModeMap = 			{ {"TRANSPARENT", TRANSPARENT}, {"FILLED", FILLED} };
static std::unordered_map<std::string, DrawMode>			DrawModeMap = 			{ {"HOVER", HOVER}, {"BASE", BASE} };
static std::unordered_map<std::string, FunctionModes>		FunctionModesMap =		{ {"VOID", VOID}, {"STRING", STRING},{"INT",INT} };
static std::unordered_map<std::string, ScrollMode>			ScrollModeMap = 		{ {"LIST", LIST}, {"SMOOTH", SMOOTH} };
static std::unordered_map<std::string, AlignmentType>		AlignmentTypeMap = 		{ {"BOTTOM_RIGHT", BOTTOM_RIGHT}, {"BOTTOM", BOTTOM}, {"BOTTOM_LEFT", BOTTOM_LEFT}, {"CENTRE", CENTRE}, {"RIGHT", RIGHT}, {"LEFT", LEFT }, {"TOP", TOP}, {"TOP_RIGHT", TOP_RIGHT}, {"TOP_LEFT", TOP_LEFT}, {"ALIGNMENT_ABSOLUTE", ALIGNMENT_ABSOLUTE } };
static std::unordered_map<std::string, PositionType>		PositionTypeMap = 		{ {"POSITION_ABSOLUTE", POSITION_ABSOLUTE}, {"POSITION_PERCENTAGE_CENTRE", POSITION_PERCENTAGE_CENTRE}, {"POSITION_PERCENTAGE_RIGHT", POSITION_PERCENTAGE_RIGHT}, {"POSITION_PERCENTAGE_LEFT", POSITION_PERCENTAGE_LEFT } };
static std::unordered_map<std::string, std::array<int, 3>>	Colors = 				{ {"WHITE", {255, 255, 255}}, {"BLACK", {0, 0, 0}}, {"RED", {255, 0, 0}}, {"BLUE", {0, 0, 255}}, {"GREEN", {0, 255, 0}}, {"YELLOW", {255, 255, 0}}, {"CYAN", {0, 255, 255}}, {"MAGENTA", {255, 0, 255}}, {"PURPLE1", {56, 0, 40}}, {"PURPLE2", {82, 16, 63}}, {"YELLOW1", {250, 166, 32}} };

static SDL_Rect windowRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };

static int roundUp(int numToRound, int multiple)
{
	if (multiple == 0)
	{
		return numToRound;
	}

	int const remainder = numToRound % multiple;
	if (remainder == 0)
	{
		return numToRound;
	}

	return numToRound + multiple - remainder;
}

static std::vector<std::string> SplitString(std::string stringToSplit, char delimeter)
{
	std::stringstream stringStream(stringToSplit);
	std::string splitString;
	std::vector<std::string> splitStrings;
	while (std::getline(stringStream, splitString, delimeter)) 
		splitStrings.push_back(splitString);
	return splitStrings;
}
