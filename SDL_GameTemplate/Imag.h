#pragma once
#include "Component.h"
#include <SDL.h>

class Imag : public Component
{
private:
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
public:
	Imag() = default;
	Imag(const char* path, SDL_Renderer* renderer);

	SDL_Texture* getTex();
	void setTex(const char* path); //sets texture of current object

	void init() override;	//initializes srcRect and destRect
	void _init();

	void update() override;

	void draw() override;	//draws the current object
};