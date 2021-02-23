#include "Imag.h"
#include "stdlib.h"
#include "TextureManager.h"


Imag::Imag(const char* path, SDL_Renderer* renderer)
{
	this->renderer = renderer;
	setTex(path);
}

SDL_Texture* Imag::getTex()
{
	return this->texture;
}

void Imag::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Imag::init()
{
	srcRect.x = 240;
	destRect.x = 240;
	srcRect.w = destRect.w = 480;
	srcRect.y = 200;
	destRect.y = 200;
	srcRect.h = destRect.h = 240;
}

void Imag::_init()
{
	srcRect.x = destRect.x = 800;
	srcRect.y = destRect.y = 544;
	srcRect.w = destRect.w = 128;
	srcRect.h = destRect.h = 64;
}

void Imag::update()
{
	
}

void Imag::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}