#pragma once
#include <AuxLib/AuxLib.h>
#include "Active_Module.h"
#include "Projectile_Manager.h"
#include "Effects.h"

struct Gun_Prototype;

class Gun : public Active_Module {
protected:
	float damage = 20;
	float projectile_mass = 0.05;
	float projectile_vel = 10;
	float projectile_radius = 0.2;
	float projectile_hp = 20;
	Projectile_Manager* projectile_manager = nullptr;
public:
	void set_projectile_manager(Projectile_Manager*);
	void import_Gun_Prototype(Gun_Prototype);
	void activate() override;
	void activate_side_effects() override;
};

struct Gun_Prototype {
	float damage = 20;
	float recharge_time = 0.5;
	float stamina_cost = 10;
	float projectile_mass = 0.05;
	float projectile_vel = 10;
	float projectile_radius = 0.2;
	float projectile_hp = 20;
	Effects_Prototype effect_prototype;
};