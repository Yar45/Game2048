#pragma once

#include <SFML/Graphics.hpp>
#include "BasicValues.h"
#include "MenuCallable.h"
#include "RoundedSquare.h"
#include "Colors.h"

class Button : public sf::Drawable, public sf::Transformable
{
public:
	sf::Font* font;
	sf::Text text;

	sf::Texture* texture;
	sf::Sprite sprite;

	sf::IntRect textureNormalPosition;
	sf::IntRect texturePressedPosition;
	sf::IntRect textureHoverPosition;

	bool isHovered;
	bool isActive;

	MenuCallable* menuCallable;
	ButtonAction action;

	size_t width;
	size_t height;
	size_t corner;

	Button(sf::Font* _font, sf::Texture* _texture, sf::IntRect _textureNormalPosition,
		sf::IntRect _texturePressedPosition, sf::IntRect _textureHoverPosition,
		std::wstring _text, size_t _width, size_t _height, size_t _corner, 
		MenuCallable* _menuCallable, ButtonAction _action)
		: font(_font), texture(_texture),
		textureNormalPosition(_textureNormalPosition), texturePressedPosition(_texturePressedPosition),
		textureHoverPosition(_textureHoverPosition),
		isHovered(false), isActive(false),
		menuCallable(_menuCallable), action(_action),
		width(_width), height(_height), corner(_corner)
	{
		text.setFont(*font);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::White);
		text.setCharacterSize(BasicValues::BUTTON_fontSize);
		text.setString(_text);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
		text.setPosition(width / 2.f, height / 2.f);
		
		sprite.setTexture(*texture);
		sprite.setTextureRect(textureNormalPosition);

		sprite.setScale((float)width / sprite.getTextureRect().width, (float)height / sprite.getTextureRect().height);
	}

	~Button() {

	}

	sf::Vector2f getSize() const {
		return sprite.getGlobalBounds().getSize();
	}

	void enableHover() {
		isActive = false;
		isHovered = true;
		sprite.setTextureRect(textureHoverPosition);

		//std::cout << "Hover Mode" << std::endl;
	}

	void enableActivation() {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left)){}

		isActive = true;
		isHovered = false;
		sprite.setTextureRect(texturePressedPosition);
		menuCallable->setMode(action);

		//std::cout << "Active Mode" << std::endl;
	}

	void disableHighlight() {
		isHovered = false;
		isActive = false;
		sprite.setTextureRect(textureNormalPosition);

		//std::cout << "No highlight Mode" << std::endl;
	}

	bool isPressed(float x, float y) {
		bool b = sprite.getGlobalBounds().contains(x, y);
		if (b) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (isActive == false) enableActivation();
				return true;
			} else {
				if (isHovered == false) enableHover();
				return false;
			}
		}
		if (isHovered == true || isActive == true) disableHighlight();
		return false;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite, states);
		target.draw(text, states);
	}
};