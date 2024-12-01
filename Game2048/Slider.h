#pragma once

#include <SFML/Graphics.hpp>
#include "MenuCallable.h"
#include "RoundedSquare.h"

class Slider : public sf::Drawable, public sf::Transformable
{
public:
	RoundedSquare sq;
	RoundedSquare border;

	sf::CircleShape knob;

	float knobOffset;

	float value;

	size_t width;
	size_t height;

	MenuCallable* menuCallable;

	Slider(size_t _width, size_t _height, size_t corner, float currentValue, MenuCallable* _menuCallable);

	void setValue(float _value);

	bool isPressed(float x, float y);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

