#include "pch.h"
#include "Button.h"

Button::Button() {
	get_sprite()->setColor(sf::Color::White);
}

void Button::step() {
	primitive_step();
	if (get_active())
		get_sprite()->setColor(sf::Color::Cyan);
}