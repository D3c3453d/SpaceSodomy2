#include "pch.h"
#include "AI.h"
#include <iomanip>

void AI::set_ship(Ship* _ship) {
	ship = _ship;
}

void AI::turn_to_angle(float angle) {
	ship->get_player()->get_command_module()->set_command(CommandModule::SHOOT, 1);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 0);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 0);

	auto cur_angle = ship->get_body()->GetAngle();
	while (cur_angle > b2_pi)
		cur_angle -= 2 * b2_pi;
	while (cur_angle < -b2_pi)
		cur_angle += 2 * b2_pi;

	//std::cout << cur_angle << " " << angle << " " << cur_angle - angle << std::endl;

	auto dif = cur_angle - angle;
	if (abs(dif) > b2_pi) {
		if (dif < 0) {
			dif += 2 * b2_pi;
		}
		else {
			dif -= 2 * b2_pi;
		}
	}

	auto dist = 2 * b2_pi;
	auto point = 0.0;
	if (abs(-2 * b2_pi - dif) < dist) {
		dist = abs(-2 * b2_pi - dif);
		point = -2 * b2_pi - dif;
	}
	if (abs(dif) < dist) {
		dist = abs(dif);
		point = dif;
	}
	if (abs(2 * b2_pi - dif) < dist) {
		dist = abs(2 * b2_pi - dif);
		point = 2 * b2_pi - dif;
	}

	//std::cout << dif << " " << dist << " " << point << std::endl;

	if (dist < 0.03) {
		//std::cout << "stab\n";
		ship->get_player()->get_command_module()->set_command(CommandModule::STABILIZE_ROTATION, 1);
	}
	else {
		auto speed = ship->get_body()->GetAngularVelocity();
		auto acceleration = ship->get_engine()->get_torque() / ship->get_body()->GetInertia();
		//std::cout << std::fixed;
		//std::cout << std::setprecision(4) << point << " " << speed << " " << acceleration << " " <<
		//	abs(point / speed) << " " << abs(speed / acceleration) << std::endl;
		if (point > 0) {
			if (abs(point / speed) > abs(speed / acceleration)) {
				//std::cout << "left\n";
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 1);
			}
			else {
				//std::cout << "right\n";
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 1);
			}
		}
		else {
			if (abs(point / speed) > abs(speed / acceleration)) {
				//std::cout << "right\n";
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_RIGHT, 1);
			}
			else {
				//std::cout << "left\n";
				ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_ANG_LEFT, 1);
			}
		}
	}
}

void AI::move_to_point(b2Vec2 point) {
	auto pos = ship->get_body()->GetPosition();
	auto speed = ship->get_body()->GetLinearVelocity();
	auto force_linear = ship->get_engine()->get_force_linear();

	auto path = point - pos;

	auto cur_angle = ship->get_body()->GetAngle();
	while (cur_angle > 2 * b2_pi)
		cur_angle -= 2 * b2_pi;
	while (cur_angle < 0)
		cur_angle += 2 * b2_pi;

	auto point_angle = aux::vec_to_angle(path) + b2_pi;
	auto dir_angle = cur_angle - point_angle;

	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_LEFT, 0);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_RIGHT, 0);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_FORWARD, 0);
	ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_BACKWARD, 0);


	auto rand = aux::random_float(0, 1, 2);
	std::cout << dir_angle << " " << rand << " " << cos(dir_angle) << " " << sin(dir_angle) << "\n";



	if (rand < abs(sin(dir_angle))) {
		if (sin(dir_angle) < 0) {
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_LEFT, 1);
		}
		else {
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_RIGHT, 1);
		}
	}

	if (rand < abs(cos(dir_angle))) {
		if (cos(dir_angle) < 0) {
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_FORWARD, 1);
		}
		else {
			ship->get_player()->get_command_module()->set_command(CommandModule::ENGINE_LIN_BACKWARD, 1);
		}
	}
}

void AI::step(Ship* _ship) {
	if (ship != nullptr) {
		turn_to_angle(aux::vec_to_angle(_ship->get_body()->GetPosition() - ship->get_body()->GetPosition()));
		move_to_point({5, 5});
	}
}

