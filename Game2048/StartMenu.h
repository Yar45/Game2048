#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MenuCallable.h"
#include "PrettySet.h"

class StartMenu : public sf::Drawable, public sf::Transformable
{
public:
	sf::RenderWindow* window;
	MenuCallable* menuCallable;

	Button * buttonStart;
	Button * buttonOptions;

	size_t buttonWidth;
	size_t buttonHeight;
	size_t buttonCorner;
	size_t buttonOffset;

	float leftOffset;
	float upOffset1;
	float upOffset2;

	StartMenu(sf::RenderWindow* _window, MenuCallable* _menuCallable,
		size_t _buttonWidth, size_t _buttonHeight, size_t _buttonCorner, size_t _buttonOffset, size_t _fontSize);

	~StartMenu();

	void updateMousePosition(float x, float y);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

