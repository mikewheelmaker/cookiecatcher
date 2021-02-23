#pragma once
#include "Component.h"
#include "GlobalVar.h"
#include <SDL.h>

class Health : public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

public:
   Health() = default;
   Health(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);	//sets texture of current object from path

	void init() override;	//initializes srcRect and destRect

	void _init(int x);		//initializes srcRect and destRect taking into account x=the x coordinate of top left corner

	void update() override;	

	void draw() override;	//draws hearts, according to the number in colBadCookie
};
