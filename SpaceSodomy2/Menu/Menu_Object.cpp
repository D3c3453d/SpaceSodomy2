#include "pch.h"
#include "Menu_Object.h"

Menu_Object::Menu_Object() {}
Menu_Object::Menu_Object(int id_, std::string texture_name_, Draw* draw_, b2Vec2 pos_, b2Vec2 scale_, sf::Color color_) {
	id = id_;
	texture_name = texture_name_;
	draw = draw_;
	pos = pos_;
	scale = scale_;
	color = color_;
}

// Get methods
int Menu_Object::get_id() {
	return id;
}
std::string Menu_Object::get_texture_name() {
	return texture_name;
}
Draw* Menu_Object::get_draw() {
	return draw;
}
b2Vec2 Menu_Object::get_pos() {
	return pos;
}
b2Vec2 Menu_Object::get_scale() {
	return scale;
}
sf::Color Menu_Object::get_color() {
	return color;
}
bool Menu_Object::get_active() {
	return active;
}

// Set methods
void Menu_Object::set_id(int id_) {
	id = id_;
}
void Menu_Object::set_texture_name(std::string texture_name_) {
	texture_name = texture_name_;
}
void Menu_Object::set_draw(Draw* draw_) {
	draw = draw_;
}
void Menu_Object::set_pos(b2Vec2 pos_) {
	pos = pos_;
}
void Menu_Object::set_scale(b2Vec2 scale_) {
	scale = scale_;
}
void Menu_Object::set_color(sf::Color color_) {
	color = color_;
}

void Menu_Object::primitive_step()
{
	if (sf::FloatRect(aux::to_vector2f(pos),
		aux::to_vector2f(scale)).contains(sf::Vector2f(sf::Mouse::getPosition())))
		active = 1;
	else
		active = 0;
	draw->image(texture_name, pos, scale, (0.0F), color);
}