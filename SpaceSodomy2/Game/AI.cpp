#include "pch.h"
#include "AI.h"

void AI::set_ship(Ship* _ship) {
	ship = _ship;
}

void AI::turn_to_angle(float angle) {
	auto cur_angle = ship->get_body()->GetAngle();
	while (cur_angle > b2_pi)
		cur_angle -= 2 * b2_pi;
	while (cur_angle < -b2_pi)
		cur_angle += 2 * b2_pi;

	std::cout << cur_angle << " " << angle << " " << abs(cur_angle - angle) << std::endl;

	ship->get_player()->get_command_module()->set_command(CommandModule::STABILIZE_ROTATION, 1);
	if (abs(cur_angle - angle) > 0.001 && 2 * b2_pi - abs(angle - cur_angle) > 0.01) {
		if (abs(angle - cur_angle) < 2 * b2_pi - abs(angle - cur_angle)) {
			if (abs(ship->get_body()->GetAngularVelocity() * 100) < abs(cur_angle - angle))
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 1);
		}
		else {
			if (abs(ship->get_body()->GetAngularVelocity() * 100) < 2 * b2_pi - abs(cur_angle - angle))
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 1);
		}
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
	ship->get_player()->get_command_module()->set_command(CommandModule::RESPAWN, 1);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 0);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 0);
	turn_to_angle(aux::vec_to_angle(_ship->get_body()->GetPosition() - ship->get_body()->GetPosition()));
}

