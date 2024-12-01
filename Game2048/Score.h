#pragma once

#include <SFML/Graphics.hpp>
#include "BasicValues.h"
#include "RoundedSquare.h"
#include "PrettySet.h"
#include "Colors.h"

class Score : public sf::Drawable, public sf::Transformable
{
public:
	RoundedSquare currentScoreSq;
	RoundedSquare maxScoreSq;

	sf::Text currentScoreText;
	sf::Text maxScoreText;

	sf::Text currentScoreTextConst;
	sf::Text maxScoreTextConst;

	size_t width;
	size_t height;
	size_t corner;
	size_t scoreOffset;
	
	Score(size_t _width, size_t _height, size_t _corner, size_t _scoreOffset, size_t currentScore, size_t maxScore);

	sf::Vector2f getSize();

private:	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

