#include "Map.h"
#include "GlobalVar.h"
#include "TextureManager.h"
#include <SDL.h>

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	background = TextureManager::LoadTexture("assets/background.png", renderer);
	margin = TextureManager::LoadTexture("assets/margin.png", renderer);
	cookie = TextureManager::LoadTexture("assets/cookie+.png", renderer);

	LoadMap(_background);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;
}

Map::Map(SDL_Renderer* renderer, int map[20][30], int x)
{
	this->renderer = renderer;
	background = TextureManager::LoadTexture("assets/background.png", renderer);
	margin = TextureManager::LoadTexture("assets/margin.png", renderer);
	cookie = TextureManager::LoadTexture("assets/cookie+.png", renderer);

	LoadMap(map);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

	this->type = x;
}

Map::~Map()
{

}

void Map::LoadMap(int arr[20][30])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			case 0:
				{
				TextureManager::Draw(background, src, dest, renderer);
					break;
				}
			case 1:
			{
				TextureManager::Draw(margin, src, dest, renderer);
				break;
			}
			case 2:
			{
				TextureManager::Draw(cookie, src, dest, renderer);
				break;
			}
			default:
				break;
			}
		}
	}
}