#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MenuCallable.h"
#include "Slider.h"
#include "PrettySet.h"

class Options : public sf::Drawable, public sf::Transformable
{
public:
	sf::RenderWindow* window;
	MenuCallable* menuCallable;

	Slider* volumeSlider;

	Button* buttonSetSize400x300;
	Button* buttonSetSize640x480;
	Button* buttonSetSize800x600;
	//Button* buttonSetFullScreen;

	size_t buttonWidth;
	size_t buttonHeight;
	size_t buttonCorner;
	size_t buttonOffset;

	size_t sliderWidth;
	size_t sliderHeight;
	size_t sliderCorner;
	size_t sliderOffset;
	size_t fontSize;

	sf::Text volumeText;

	float leftOffset;
	float upOffset1;
	float upOffset2;

	Options(sf::RenderWindow* _window, MenuCallable* _menuCallable, float currentVolume,
		size_t _sliderWidth, size_t _sliderHeight, size_t _sliderCorner, size_t _sliderOffset, size_t _fontSize,
		size_t _buttonWidth, size_t _buttonHeight, size_t _buttonCorner, size_t _buttonOffset);

	~Options();

	void updateMousePosition(float x, float y);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
