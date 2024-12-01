#pragma once

#include <SFML/Graphics.hpp>
#include "BasicValues.h"
#include "RoundedSquare.h"
#include "Colors.h"
#include "PrettySet.h"

class GameCell : public sf::Drawable, public sf::Transformable
{
	protected:
		long long num;

	public:
		RoundedSquare sq;
		sf::Text text_num;

		GameCell(size_t _cellLength, size_t _cellCorner, long long _num);
		~GameCell();

		void setNum(long long num);
		long long getNum() const;

		GameCell& operator = (unsigned int _num);
		GameCell& operator = (const GameCell& cell);
		GameCell& operator * (unsigned int _num);
		bool operator == (unsigned int _num);
		bool operator == (const GameCell& cell);
		bool operator != (unsigned int _num);
		bool operator != (const GameCell& cell);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

