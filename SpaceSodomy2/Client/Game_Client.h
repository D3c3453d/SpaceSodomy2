#pragma once
#include <Game/Game.h>
#include <Draw/Draw.h>

class Game_Client : public Game {
private:
	Draw* draw = nullptr;
public:
	// Set methods
	void set_draw(Draw* _draw);

	void display(int id);
};

