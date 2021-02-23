#pragma once
#include "Component.h"
#include "Player.h"
#include "GlobalVar.h"
#include "SDL.h"

//types of cookies
enum class CookieType {
	good,
	bad,
	mini
};

class Cookie : public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	SDL_Rect colRect;
	CookieType type;
	int dx;	//used to set speed of falling cookies according to the score

public:
	
	Cookie() = default;
    Cookie(const char* path, SDL_Renderer* renderer);

	SDL_Rect getColRect();	//gets the colRect of the current object

	CookieType getType();	//gets the type of current cookie object
	void setType(CookieType type); //sets the type of current object to type

	int getDX();			//gets dx of current object
	void setDX(int dx);		//sets dx of current object to dx

	SDL_Texture* getTex();
	void setTex(const char* path);	//sets the texture of the current object

	void init() override;	//initializes srcRect, destRect and colRect

	void update() override;	//updates the position
	bool _update(int s);	//updates the position taking into account the score s

	void draw() override;	//draws current object
};