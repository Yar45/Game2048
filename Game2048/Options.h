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
		size_t _buttonWidth, size_t _buttonHeight, size_t _buttonCorner, size_t _buttonOffset)
		: window(_window), menuCallable(_menuCallable), sliderWidth(_sliderWidth), sliderHeight(_sliderHeight),
		sliderCorner(_sliderCorner), sliderOffset(_sliderOffset), fontSize(_fontSize),
		buttonWidth(_buttonWidth), buttonHeight(_buttonHeight), buttonCorner(_buttonCorner), buttonOffset(_buttonOffset)
	{
		leftOffset = window->getSize().x / 2.f - sliderWidth / 2.f;
		upOffset1 = window->getSize().y / 2.f - buttonWidth;

		volumeText.setFont(*PrettySet::font);
		volumeText.setFillColor(sf::Color::White);
		volumeText.setOutlineColor(sf::Color::White);
		volumeText.setCharacterSize(fontSize);
		volumeText.setString(L"���������");
		volumeText.setOrigin(volumeText.getGlobalBounds().getSize() / 2.f + volumeText.getLocalBounds().getPosition());
		volumeText.setPosition(window->getSize().x / 2.f, upOffset1);

		upOffset2 = upOffset1 + volumeText.getGlobalBounds().getSize().y + 20;

		volumeSlider = new Slider(sliderWidth, sliderHeight, sliderCorner, currentVolume, menuCallable);
		volumeSlider->setPosition(leftOffset, upOffset2);

		buttonSetSize400x300 = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"400 x 300", buttonWidth, buttonHeight/2, buttonCorner, menuCallable, RESIZE_400x300);
		buttonSetSize400x300->setPosition(leftOffset, volumeSlider->getPosition().y + sliderHeight + 20);

		buttonSetSize640x480 = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"640 x 480", buttonWidth, buttonHeight/2, buttonCorner, menuCallable, RESIZE_640x480);
		buttonSetSize640x480->setPosition(leftOffset, buttonSetSize400x300->getPosition().y + buttonHeight/2 + 20);

		buttonSetSize800x600 = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"800 x 600", buttonWidth, buttonHeight/2, buttonCorner, menuCallable, RESIZE_800x600);
		buttonSetSize800x600->setPosition(leftOffset, buttonSetSize640x480->getPosition().y + buttonHeight/2 + 20);

		//buttonSetFullScreen = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"������ �����", buttonWidth, buttonHeight/2, buttonCorner, menuCallable, RESIZE_FULLSCREEN);
		//buttonSetFullScreen->setPosition(leftOffset, buttonSetSize800x600->getPosition().y + buttonHeight/2 + 20);
	}

	~Options() {
		delete volumeSlider;
	}

	void updateMousePosition(float x, float y) {
		sf::Vector2f pos1 = volumeSlider->getPosition();
		sf::Vector2f pos2 = buttonSetSize400x300->getPosition();
		sf::Vector2f pos3 = buttonSetSize640x480->getPosition();
		sf::Vector2f pos4 = buttonSetSize800x600->getPosition();
		//sf::Vector2f pos5 = buttonSetFullScreen->getPosition();
		bool b1 = volumeSlider->isPressed(x - pos1.x, y - pos1.y);
		bool b2 = buttonSetSize400x300->isPressed(x - pos2.x, y - pos2.y);
		bool b3 = buttonSetSize640x480->isPressed(x - pos3.x, y - pos3.y);
		bool b4 = buttonSetSize800x600->isPressed(x - pos4.x, y - pos4.y);
		//bool b5 = buttonSetFullScreen->isPressed(x - pos5.x, y - pos5.y);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(volumeText, states);
		target.draw(*volumeSlider, states);
		target.draw(*buttonSetSize400x300, states);
		target.draw(*buttonSetSize640x480, states);
		target.draw(*buttonSetSize800x600, states);
		//target.draw(*buttonSetFullScreen, states);
	}
};
