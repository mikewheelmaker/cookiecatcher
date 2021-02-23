#include "Player.h"
#include "stdlib.h"
#include "TextureManager.h"

Player::Player(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

SDL_Rect Player::getColRect()
{
	return this->colRect;
}

void Player::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init()
{
   srcRect.x = destRect.x = 32;
   srcRect.y = destRect.y = 528;
   srcRect.w = destRect.w = colRect.w = 160;
   srcRect.h = destRect.h = colRect.h = 80;
   colRect.x = destRect.x;
   colRect.y = destRect.y;
}

void Player::update()
{
	const Uint8* currentKey = SDL_GetKeyboardState(NULL);

	if (currentKey[SDL_SCANCODE_UP])
	{
		destRect.y = destRect.y - 10;
		if (destRect.y < -80)
		{
			destRect.y += 10;
		}
	}
	else if (currentKey[SDL_SCANCODE_DOWN])
	{
		destRect.y = destRect.y + 10;
		if (destRect.y > 528)
		{
			destRect.y -= 10;
		}
	}
	else if (currentKey[SDL_SCANCODE_LEFT])
	{
		destRect.x = destRect.x - 10;
		if (destRect.x < 20)
		{
			destRect.x += 10;
		}
	}
	else if (currentKey[SDL_SCANCODE_RIGHT])
	{
		destRect.x = destRect.x + 10;
		if (destRect.x > 640)
		{
			destRect.x -= 10;
		}
	}
	colRect.x = destRect.x;
	colRect.y = destRect.y;
}

void Player::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}