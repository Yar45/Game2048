#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "RoundedSquare.h"

#define PATH_TEXTURE "assets/UI.png"
#define PATH_TEXTURE_BACKGROUND_1 "assets/SpaceBackground1.png"
#define PATH_FONT "assets/RubikMonoOne-Regular.ttf"

class PrettySet
{
public:
	static inline sf::Font* font;
	static inline sf::Texture* texture;
	static inline sf::Texture* textureBackground1;

	static inline sf::Text* currentScoreLink = nullptr;
	static inline sf::Text* maxScoreLink = nullptr;
	static inline RoundedSquare* currentScoreSquareLink = nullptr;
	static inline RoundedSquare* maxScoreSquareLink = nullptr;

	static inline sf::Text* currentScoreResultLink = nullptr;
	static inline sf::Text* currentScoreResultConstLink = nullptr;

	static inline const sf::IntRect textureNormalPosition { 5, 52, 40, 40 };
	static inline const sf::IntRect texturePressedPosition { 53, 52, 40, 40 };
	static inline const sf::IntRect textureHoverPosition {101, 52, 40, 40};

	static inline const sf::IntRect textureNormalPosition2{ 3, 272, 162-3, 355-272 };
	static inline const sf::IntRect textureHoverPosition2{ 3, 181, 162-3, 264-181 };

	static inline const sf::IntRect textureSquareNormalPosition{ 176, 272, 255 - 176, 354 - 272 };
	static inline const sf::IntRect textureSquareHoverPosition{ 176, 181, 255 - 176, 263 - 181 };

	static inline const sf::IntRect textureCellPosition1{ 3, 2, 44, 44 };
	static inline const sf::IntRect textureCellPosition2{ 51, 2, 44, 44 };
	static inline const sf::IntRect textureCellPosition3{ 99, 2, 44, 44 };
	static inline const sf::IntRect textureCellPosition4{ 147, 2, 44, 44 };

	PrettySet() {}
	~PrettySet() {}

	void static loadTexture() {
		texture = new sf::Texture;
		if (!texture->loadFromFile(PATH_TEXTURE)) {
			std::cout << "Texture error..." << std::endl;
		}

		textureBackground1 = new sf::Texture;
		if (!textureBackground1->loadFromFile(PATH_TEXTURE_BACKGROUND_1)) {
			std::cout << "Texture 2 error..." << std::endl;
		}
	}

	void static loadFont() {
		font = new sf::Font;
		if (!font->loadFromFile(PATH_FONT)) {
			std::cout << "Font error..." << std::endl;
		}
	}

	void static setScoreLinks(sf::Text* _currentScoreLink, sf::Text* _maxScoreLink, RoundedSquare* _currentScoreSquareLink, RoundedSquare* _maxScoreSquareLink) {
		currentScoreLink = _currentScoreLink;
		maxScoreLink = _maxScoreLink;
		currentScoreSquareLink = _currentScoreSquareLink;
		maxScoreSquareLink = _maxScoreSquareLink;
	}

	void static setScoreResultLinks(sf::Text* _currentScoreResultLink, sf::Text* _currentScoreResultConstLink) {
		currentScoreResultLink = _currentScoreResultLink;
		currentScoreResultConstLink = _currentScoreResultConstLink;
	}
};