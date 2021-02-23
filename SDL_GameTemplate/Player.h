#pragma once
#include "Component.h"
#include "GlobalVar.h"
#include "SDL.h"

class Player : public Component
{
private:
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	SDL_Rect colRect;	//collision SDL_Rect, set to be the same as the future destRect

public:
	Player() = default;
    Player(const char* path, SDL_Renderer* renderer);

	SDL_Rect getColRect();	//gets colRect, used for collision detection in Collision.h

	void setTex(const char* path);	//sets texture of current object

	void init() override;	//initializes srcRect and destRect

	void update() override;	//updates the position of the basket according to the inputs given from the keyboard

	void draw() override;	//draws the basket
};