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
		MenuCallable* _menuCallable, ButtonAction _action);

	~Button();

	sf::Vector2f getSize() const;

	void enableHover();

	void enableActivation();

	void disableHighlight();

	bool isPressed(float x, float y);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};