#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include "Ship.h"
#include "Engine.h"
#include "Player.h"
#include "Wall.h"
#include "Gun.h"
#include "Projectile.h"
#include "Projectile_Manager.h"
#include "Collision_Filter.h"
#include "Contact_Table.h"
#include <box2d/box2d.h>
#include <AuxLib/AuxLib.h>
#include <memory>

class Game {
protected:
	// Collision control
	Collision_Filter collision_filter;

	// Time step
	float dt = 0;

	// Objects' systems
	std::set<Ship*> ships;
	std::set<Player*> players;
	std::set<Engine*> engines;
	std::map<int, Command_Module*> command_modules;
	std::set<Wall*> walls;
	std::set<Active_Module*> active_modules;
	std::set<Projectile*> projectiles;
	Projectile_Manager projectile_manager;
	b2World physics = b2World(b2Vec2_zero);

	// Contact table (stores pairs which are in contact)
	Contact_Table contact_table;

	// Path to the map
	std::string map_path = "";

	// Create functions
	b2Body* create_round_body(b2Vec2 pos, float angle, float radius, float mass);
	Ship* create_ship(Player* player, b2Vec2 pos, float angle);
	Wall* create_wall(std::vector<b2Vec2> vertices, int orientation = Wall::OUTER, float restitution = 0.5);
	Projectile* create_projectile(Projectile_Def);

	// Delete functions
	void delete_projectile(Projectile*);

	 // Processing functions
	void process_engines();
	void process_projectiles();
	void process_active_modules();
	void process_projectlie_manager();
	void process_physics();
public:
	Game();
	// Sets command to player with id=id
	void apply_command(int id, int command, int val);
	void step(float dt);
	// Loads walls from file (returns 1 if everything is correct)
	int load_map(std::string path);
	// Clears everyrhing
	void clear();
	// Encodes class into string
	std::string encode();
	// Decodes class from string
	void decode(std::string source);
	// Creates new player
	Ship* create_player(int id, sf::Color color, std::string name, b2Vec2 pos, float angle);
	//Deletes player
	void del_player(int id);
};

