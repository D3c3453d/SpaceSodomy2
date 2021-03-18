#include "pch.h"
#include "Gun.h"
#include <iostream>

void Gun::set_projectile_manager(Projectile_Manager* _projectile_manager) {
	projectile_manager = _projectile_manager;
}

void Gun::activate() {
	Projectile_Def projectile_def;

	float vel_val = 10;

	projectile_def.pos = body->GetPosition();
	projectile_def.vel = body->GetLinearVelocity();
	projectile_def.angle = body->GetAngle();
	b2Vec2 delta_vel = vel_val * aux::angle_to_vec(projectile_def.angle);
	projectile_def.vel += delta_vel;
	projectile_def.player = player;
	projectile_def.damage = damage;

	Event_Def event_def;
	event_def.name = "gn";
	event_def.body = body;
	event_manager->create_event(event_def);

	projectile_manager->create_projectile(projectile_def);
}