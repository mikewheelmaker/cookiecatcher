#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Cookie.h"
#include "Health.h"
#include "Imag.h"
#include "Collision.h"
#include <SDL.h>
#include <SDL_image.h>

Collision* collider = new Collision;
Imag* _start;
Imag* _end;
Imag* plate;
Map* map;
Player* player;
Cookie* badcookie;
Cookie** goodcookies;
Cookie** minicookies;
Health** health;

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr)
{

}

Game::~Game()
{
   delete player;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map(renderer, _startscreen, 0);
	_start = new Imag("assets/start.png", renderer);
	_start->init();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: {
		isRunning = false;
		break;
	}
	default:
		break;
	}
}

void Game::update()
{
	int m = map->getMapType();
	if (m == 0)
	{
		const Uint8* _currentKey = SDL_GetKeyboardState(NULL);
		if (_currentKey[SDL_SCANCODE_RETURN])
		{
			map = new Map(renderer, _background, 1);
			delete[] _start;
			_start = nullptr;

			player = new Player("assets/basket.png", renderer);
			player->init();

			plate = new Imag("assets/plate0.png", renderer);
			plate->_init();

			collider->setScore(0);
			collider->setColBC(0);

			badcookie = new Cookie("assets/badcookie.png", renderer);
			badcookie->setType(CookieType::bad);
			badcookie->init();

			goodcookies = new Cookie*[5];
			for (int i = 0; i < 5; ++i)
			{
				goodcookies[i] = new Cookie("assets/cookie.png", renderer);
				goodcookies[i]->setType(CookieType::good);
				goodcookies[i]->init();
			}

			minicookies = new Cookie*[3];
			for (int i = 0; i < 3; ++i)
			{
				minicookies[i] = new Cookie("assets/cookie.png", renderer);
				minicookies[i]->setType(CookieType::mini);
				minicookies[i]->init();
			}

			health = new Health*[5];
			x = 736;
			for (int j = 0; j < 5; ++j)
			{
				health[j] = new Health("assets/heart.png", renderer);
				health[j]->_init(x);
				x -= 32;
			}
		}
		else if (_currentKey[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}
	}
	else if (m == 1)
	{
		int s = collider->getScore();
		int colBC = collider->getColBC();

		if ((s < 0) || (colBC >= 5))
		{
			map = new Map(renderer, _endscreen, 2);
			_end = new Imag("assets/end.png", renderer);
			_end->init();

			delete[] player;
			player = nullptr;
			delete[] plate;
			plate = nullptr;
			delete[] collider;
			collider = nullptr;
			delete[] badcookie;
			badcookie = nullptr;

			for (int i = 0; i < 5; ++i)
			{
				delete[] goodcookies[i];
				goodcookies[i] = nullptr;
				delete[] health[i];
				health[i] = nullptr;
			}
			goodcookies = nullptr;
			health = nullptr;

			for (int i = 0; i < 3; ++i)
			{
				delete[] minicookies[i];
				minicookies[i] = nullptr;
			}
			minicookies = nullptr;
		}
		else
		{
			player->update();

			if (s >= 100 && s < 200)
			{
				SDL_DestroyTexture(plate->getTex());
				//delete[] plate;
				//plate = nullptr;
				plate = new Imag("assets/plate1.png", renderer);
				plate->_init();
			}
			else if (s >= 200 && s < 300)
			{
				SDL_DestroyTexture(plate->getTex());
				//delete[] plate;
				//plate = nullptr;
				plate = new Imag("assets/plate2.png", renderer);
				plate->_init();
			}
			else if (s >= 300 && s < 400)
			{
				SDL_DestroyTexture(plate->getTex());
				//delete[] plate;
				//plate = nullptr;
				plate = new Imag("assets/plate3.png", renderer);
				plate->_init();
			}
			else if (s>=400)
			{
				SDL_DestroyTexture(plate->getTex());
				//delete[] plate;
				//plate = nullptr;
				plate = new Imag("assets/plate4.png", renderer);
				plate->_init();
			}

			bool checkOut = badcookie->_update(s);
			bool checkC = (collider->colDet(player, badcookie));
			if (checkC == true)
			{
				collider->setScore(s -= 50);
				collider->setColBC(++colBC);
				badcookie->init();
			}

			int i = 0;
			while (i < 5)
			{
				
				bool checkOut = goodcookies[i]->_update(s);
				if (checkOut)
				{
					collider->setScore(s -= 10);
				}
				bool checkC = (collider->colDet(player, goodcookies[i]));
				if (checkC == true)
				{
					collider->setScore(s += 10);
					goodcookies[i]->init();
				}
				++i;
			}

			int j = 0;
			while (j < 3)
			{
				bool checkOut = minicookies[j]->_update(s);
				++j;
			}
		}
	}
	else if (m == 2)
	{
		const Uint8* _currentKey = SDL_GetKeyboardState(NULL);
		if (_currentKey[SDL_SCANCODE_RETURN])
		{
			map = new Map(renderer, _background, 1);

			delete[] _end;
			_end = nullptr;

			plate = new Imag("assets/plate0.png", renderer);
			plate->_init();

			collider = new Collision;
			collider->setScore(0);
			collider->setColBC(0);

			player = new Player("assets/basket.png", renderer);
			player->init();

			badcookie = new Cookie("assets/badcookie.png", renderer);
			badcookie->setType(CookieType::bad);
			badcookie->init();

			goodcookies = new Cookie*[5];
			for (int i = 0; i < 5; ++i)
			{
				goodcookies[i] = new Cookie("assets/cookie.png", renderer);
				goodcookies[i]->setType(CookieType::good);
				goodcookies[i]->init();
			}

			minicookies = new Cookie*[3];
			for (int i = 0; i < 3; ++i)
			{
				minicookies[i] = new Cookie("assets/cookie.png", renderer);
				minicookies[i]->setType(CookieType::mini);
				minicookies[i]->init();
			}

			health = new Health*[5];
			x = 736;
			for (int j = 0; j < 5; ++j)
			{
				health[j] = new Health("assets/heart.png", renderer);
				health[j]->_init(x);
				x -= 32;
			}
		}
		else if(_currentKey[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	int colBC = collider->getColBC();

	if (map != nullptr)
	{
		map->DrawMap();
	}

	if (plate != nullptr)
	{
		plate->draw();
	}

	if (_start != nullptr)
	{
		_start->draw();
	}

	if (_end != nullptr)
	{
		_end->draw();
	}

	if (player != nullptr)
	{
		player->draw();
	}
	
	if (badcookie != nullptr)
	{
		badcookie->draw();
	}

	if (goodcookies != nullptr)
	{
		for (int i = 0; i < 5; ++i)
		{
			goodcookies[i]->draw();
		}
	}
	
	if (minicookies != nullptr)
	{
		for (int i = 0; i < 3; ++i)
		{
			minicookies[i]->draw();
		}
	}
	
	if (health != nullptr)
	{
		switch (colBC)
		{
			case 0:
			{
				for (int i = 0; i < 5; ++i)
				{
					health[i]->draw();
				}
				break;
			}

			case 1:
			{
				for (int i = 0; i < 4; ++i)
				{
					health[i]->draw();
				}
				break;
			}

			case 2:
			{
				for (int i = 0; i < 3; ++i)
				{
					health[i]->draw();
				}
				break;
			}

			case 3:
			{
				for (int i = 0; i < 2; ++i)
				{
					health[i]->draw();
				}
				break;
			}

			case 4:
			{
				health[0]->draw();
				break;
			}
		}
	}
	
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}