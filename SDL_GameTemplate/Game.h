#pragma once
#include <SDL.h>
#include "GlobalVar.h"

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
public:
	
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean() const;

	bool running() const { return isRunning; }
};
