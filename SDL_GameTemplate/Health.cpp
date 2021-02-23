#include "Health.h"
#include "stdlib.h"
#include "TextureManager.h"

Health::Health(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Health::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}


void Health::init()
{
	srcRect.x = destRect.x = 768;
	srcRect.y = destRect.y = 608;
    srcRect.w = srcRect.h = destRect.w = destRect.h = 32;
}

void Health::_init(int x)
{
	srcRect.x = destRect.x = x;
	srcRect.y = destRect.y = 608;
	srcRect.w = srcRect.h = destRect.w = destRect.h = 32;
}

void Health::update()
{
    
}


void Health::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}