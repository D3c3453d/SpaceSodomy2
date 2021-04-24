#include "pch.h"
#include "Gun.h"
#include <iostream>

void Gun::set_projectile_manager(Projectile_Manager* _projectile_manager) {
	projectile_manager = _projectile_manager;
}

void Gun::import_Gun_Prototype(Gun_Prototype def) {
	damage = def.damage;
	recharge_time = def.recharge_time;
	stamina_consumption = def.stamina_consumption;
	projectile_mass = def.projectile_mass;
	projectile_vel = def.projectile_vel;
	projectile_radius = def.projectile_radius;
	projectile_hp = def.projectile_hp;
	effects_prototype = &def.effect_prototype;
}

void Gun::activate() {
	Projectile_Def projectile_def;

	float vel_val = projectile_vel;

	projectile_def.pos = body->GetPosition();
	projectile_def.vel = body->GetLinearVelocity();
	projectile_def.angle = body->GetAngle();
	b2Vec2 delta_vel = vel_val * aux::angle_to_vec(projectile_def.angle);
	projectile_def.vel += delta_vel;
	projectile_def.player = player;
	projectile_def.damage = damage;
	projectile_def.radius = projectile_radius;
	projectile_def.mass = projectile_mass;
	projectile_def.hp = projectile_hp;
	projectile_def.effects_prototype = effects_prototype;
	// Recoil
	if (!(effects->get_effect(Effects::BERSERK)->get_counter()->get() > 0)) {
		body->ApplyLinearImpulseToCenter(-projectile_def.mass * delta_vel, 1);
	}

	Event_Def event_def;
	event_def.name = "gn";
	event_def.body = body;
	event_manager->create_event(event_def);

	projectile_manager->create_projectile(projectile_def);
}