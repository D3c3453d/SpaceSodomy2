#include "pch.h"
#include "AI.h"

void AI::set_ship(Ship* _ship) {
	ship = _ship;
}

void AI::turn_to_angle(float angle) {
	auto cur_angle = ship->get_body()->GetAngle();

	if (abs(cur_angle - angle) > b2_epsilon) {
		if (abs(angle - cur_angle) > 2 * b2_pi - abs(angle - cur_angle))
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 1);
		else
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 1);
	}
}

void AI::move_to_point(b2Vec2 point) {
	auto pos = ship->get_body()->GetPosition();
	auto speed = ship->get_body()->GetLinearVelocity();
	auto force_linear = ship->get_engine()->get_force_linear();

	auto path = point - pos;
	auto point_angle = aux::vec_to_angle(path);
	turn_to_angle(point_angle);
}

void AI::step(Ship* _ship) {
	turn_to_angle(aux::vec_to_angle(_ship->get_body()->GetPosition() - ship->get_body()->GetPosition()));
}

