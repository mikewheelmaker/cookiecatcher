#include "Cookie.h"
#include "stdlib.h"
#include "TextureManager.h"

Cookie::Cookie(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
	setTex(path);
}

SDL_Texture* Cookie::getTex()
{
	return this->texture;
}

void Cookie::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

SDL_Rect Cookie::getColRect()
{
	return this->colRect;
}

CookieType Cookie::getType()
{
	return this->type;
}

void Cookie::setType(CookieType type)
{
	this->type = type;
}

int Cookie::getDX()
{
	return this->dx;
}

void Cookie::setDX(int dx)
{
	this->dx = dx;
}

void Cookie::init()
{
	switch (type)
	{
		case CookieType::good:
		{
			srcRect.x = destRect.x = rand() % 656 + 32;
			srcRect.y = destRect.y = -rand() % 1000 - 80;
			srcRect.w = srcRect.h = destRect.w = destRect.h = colRect.h = colRect.w = 80;
			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}

		case CookieType::bad:
		{
			srcRect.x = destRect.x = rand() % 656 + 32;
			srcRect.y = destRect.y = -rand() % 1000 - 80;
			srcRect.w = srcRect.h = destRect.w = destRect.h = colRect.h = colRect.w = 80;
			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}
			
		case CookieType::mini:
		{
			srcRect.x = destRect.x = rand() % 96 + 800;
			srcRect.y = destRect.y = -rand() % 100 - 80;
			srcRect.w = srcRect.h = destRect.w = destRect.h = colRect.h = colRect.w = 40;
			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}
			
		default:
		{
			exit(EXIT_FAILURE);
			break;
		}
	}
}

void Cookie::update()
{
	
}

bool Cookie::_update(int s)
{
	switch (type)
	{
		case CookieType::good:
		{
			if (s < 100)
			{
				setDX(4);
			}
			else if (s < 200)
			{
				setDX(5);
			}
			else if (s < 300)
			{
				setDX(6);
			}
			else
			{
				setDX(7);
			}

			destRect.y += this->dx;
			if (destRect.y > 528)
			{
				destRect.x = rand() % 656 + 32;
				destRect.y = -80;
				colRect.x = destRect.x;
				colRect.y = destRect.y;
				return true;
			}

			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}
		
		case CookieType::bad:
		{
			if (s < 100)
			{
				setDX(5);
			}
			else if(s < 200)
			{
				setDX(6);
			}
			else if (s < 300)
			{
				setDX(7);
			}
			else
			{
				setDX(8);
			}

			destRect.y += this->dx;
			if (destRect.y > 528)
			{
				destRect.x = rand() % 656 + 32;
				destRect.y = -80;
			}

			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}
		
		case CookieType::mini:
		{
			setDX(3);

			destRect.y += this->dx;
			if (destRect.y > 528)
			{
				destRect.x = rand() % 96 + 800;
				destRect.y = -80;
			}

			colRect.x = destRect.x;
			colRect.y = destRect.y;
			break;
		}
		
		default:
		{
			exit(EXIT_FAILURE);
			break;
		}
	}
	return false;
}

void Cookie::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}