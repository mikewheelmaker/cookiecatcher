#pragma once
#include <SDL.h>
#include "stdlib.h"
#include "Player.h"
#include "Cookie.h"

class Collision : public Player, public Cookie
{
private:
	int score;			//modifiable by getting /*and/or missing*/ good cookies
	int colBadCookie;   //number of collisions between player and bad cookies
public:
	Collision() = default;

	int getScore();
	void setScore(int x);

	int getColBC();			//gets colBadCookie of current object
	void setColBC(int x);	//sets colBadCookie of current object to be xs

	bool colDet(Player* p, Cookie *c);	//collision detection function
};