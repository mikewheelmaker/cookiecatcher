#pragma once
#include <SDL_image.h>
#include "GlobalVar.h"

class Map
{
private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* background;
	SDL_Texture* margin;
	SDL_Texture* cookie;

	int map[20][30];
	int type;

public:
	Map(SDL_Renderer* renderer);
	Map(SDL_Renderer* renderer, int map[20][30], int x);	//constructor that initializes map with a given array and specifies type
	~Map();

	void LoadMap(int arr[20][30]);	//loads the given array
	void DrawMap();					//draws the map
	int getMapType() { return this->type; }	//gets the map type
};