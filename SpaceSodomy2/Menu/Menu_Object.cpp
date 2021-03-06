#include "pch.h"
#include "Menu_Object.h"

Menu_Object::Menu_Object() {}
Menu_Object::Menu_Object(int id_, std::string texture_name_, Draw* draw_, b2Vec2 pos_, b2Vec2 scale_, sf::Color color_, b2Vec2* mouse_pos_, aux::Keyboard* keyboard_) {
	id = id_;
	texture_name = texture_name_;
	draw = draw_;
	pos = pos_;
	scale = scale_;
	color = color_;
	mouse_pos = mouse_pos_;
	keyboard = keyboard_;
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
bool Menu_Object::get_use_picture_scale() {
	return use_picture_scale;
}
bool Menu_Object::get_image_active() {
	return image_active;
}
b2Vec2 Menu_Object::get_scale() {
	return scale;
}
sf::Color Menu_Object::get_color() {
	return color;
}
b2Vec2* Menu_Object::get_mouse_pos() {
	return mouse_pos;
}
aux::Keyboard* Menu_Object::get_keyboard() {
	return keyboard;
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
void Menu_Object::set_use_picture_scale(bool use_picture_scale_) {
	use_picture_scale = use_picture_scale_;
}
void Menu_Object::set_image_active(bool image_active_) {
	image_active = image_active_;
}
void Menu_Object::set_scale(b2Vec2 scale_) {
	scale = scale_;
}
void Menu_Object::set_color(sf::Color color_) {
	color = color_;
}
void Menu_Object::set_mouse_pos(b2Vec2* mouse_pos_) {
	mouse_pos = mouse_pos_;
}
void Menu_Object::set_keyboard(aux::Keyboard* keyboard_) {
	keyboard = keyboard_;
}

void Menu_Object::primitive_step()
{
	b2Vec2 mid = aux::to_b2Vec2(sf::Vector2f(draw->get_window()->getSize()));
	mid.x /= 2;
	mid.y /= 2;
	b2Vec2 rect_pos = pos;
	if (use_picture_scale)
		scale = aux::to_b2Vec2(sf::Vector2f(draw->get_texture(texture_name)->getSize()));
	if (aux::rect_contains(rect_pos + mid, scale, *mouse_pos))
		active = 1;
	else
		active = 0;
	if (image_active)
		draw->image(texture_name, pos, scale, 0, color);
}