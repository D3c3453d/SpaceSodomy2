#pragma once
#include "Ship.h"
#include <AuxLib/AuxLib.h>

class AI {
private:
	Ship* ship;

public:
	void set_ship(Ship* _ship);
	void move_to_point(b2Vec2 point);
	void turn_to_angle(float angle);

	void step(Ship* _ship);
};

