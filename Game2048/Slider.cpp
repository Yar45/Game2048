#include "Slider.h"

Slider::Slider(size_t _width, size_t _height, size_t corner, float currentValue, MenuCallable* _menuCallable)
	: sq(_width, _height, corner), border(_width, _height * 7, corner), width(_width), height(_height), menuCallable(_menuCallable)
{
	knob = sf::CircleShape(height);
	knobOffset = height / 2 - knob.getRadius();

	border.setPosition(0, sq.getPosition().y - height * 3);
	border.setFillColor(sf::Color(255, 0, 0, 100));

	setValue(currentValue);
}

void Slider::setValue(float _value) {
	value = _value;

	knob.setPosition(width * value - knob.getRadius(), knobOffset);

	if (value > 0.02f) {
		menuCallable->setVolume(value);
	} else {
		menuCallable->setVolume(0);
	}
	
}

bool Slider::isPressed(float x, float y) {
	if (x >= 0 && x <= width && y + height * 3 >= 0 && y <= height * 4) {
		//bool b = sq.getGlobalBounds().contains(x, y);
		bool b = border.getGlobalBounds().contains(x, y);

		//std::cout << "x: " << x << " y: " << y << " float: " << x / width << " pos: " << x - knob.getRadius() << std::endl;
		if (b) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				setValue(x / width);
				return true;
			}
		}
	}

	return false;
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	//target.draw(border, states);
	target.draw(sq, states);
	target.draw(knob, states);
}
