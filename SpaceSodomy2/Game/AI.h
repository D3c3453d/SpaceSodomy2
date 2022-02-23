#pragma once
#include <functional>
#include "Ship.h"
#include <AuxLib/AuxLib.h>

class AI {
private:
	Ship* ship;

public:
	void set_ship(Ship* _ship);
	void move_to_point(b2Vec2 point);
	bool turn_to_angle(float angle);
	void shoot(Ship* ship, std::function<b2Vec2(b2Vec2, float)> beam_intersect);

	void step(Ship* _ship, std::function<b2Vec2(b2Vec2, float)> beam_intersect);
};

