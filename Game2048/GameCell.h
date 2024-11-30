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

		GameCell(size_t _cellLength, size_t _cellCorner, long long _num) : sq(_cellLength, _cellLength, _cellCorner), num(_num) {
			text_num.setFont(*PrettySet::font);
			text_num.setFillColor(sf::Color::Black);
			text_num.setOutlineColor(sf::Color::Black);
			text_num.setCharacterSize(BasicValues::FIELD_cellFontSize);
			if (num != 0)
				text_num.setString(std::to_string(num));
			//text_num.setString("2048");

			text_num.setOrigin(text_num.getGlobalBounds().getSize() / 2.f + text_num.getLocalBounds().getPosition());
			text_num.setPosition(sq.getGlobalBounds().getSize() / 2.f);

			sq.setFillColor(Colors::color_1);
		}

		void setNum(long long num) {
			this->num = num;
			if (num != 0) {
				// TODO:// Здесь вылетает ошибка иногда почему-то (text_num.setOrigin(text_num.getGlobalBounds().getSize() / 2.f + text_num.getLocalBounds().getPosition());)
				text_num.setString(std::to_string(num));
				text_num.setOrigin(text_num.getGlobalBounds().getSize() / 2.f + text_num.getLocalBounds().getPosition());
				text_num.setPosition(sq.getGlobalBounds().getSize() / 2.f);
			} else {
				text_num.setString("");
			}

			switch (num)
			{
			case 0:
				sq.setFillColor(Colors::color_1);
				break;
			case 2:
				sq.setFillColor(Colors::color_2);
				break;
			case 4:
				sq.setFillColor(Colors::color_3);
				break;
			case 8:
				sq.setFillColor(Colors::color_4);
				break;
			case 16:
				sq.setFillColor(Colors::color_5);
				break;
			case 32:
				sq.setFillColor(Colors::color_6);
				break;
			case 64:
				sq.setFillColor(Colors::color_7);
				break;
			case 128:
				sq.setFillColor(Colors::color_8);
				break;
			case 256:
				sq.setFillColor(Colors::color_9);
				break;
			case 512:
				sq.setFillColor(Colors::color_10);
				break;
			case 1024:
				sq.setFillColor(Colors::color_11);
				break;
			case 2048:
				sq.setFillColor(Colors::color_12);
				break;
			default:
				break;
			}
		}

		long long getNum() const {
			return num;
		}

		GameCell& operator = (unsigned int _num) {
			num = _num;
			return *this;
		}

		GameCell& operator = (const GameCell& cell) {
			num = cell.num;
			return *this;
		}

		GameCell& operator * (unsigned int _num) {
			num *= _num;
			return *this;
		}

		bool operator == (unsigned int _num) {
			return num == _num;
		}

		bool operator == (const GameCell& cell) {
			return num == cell.num;
		}

		bool operator != (unsigned int _num) {
			return num != _num;
		}

		bool operator != (const GameCell& cell) {
			return num != cell.num;
		}

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(sq, states);
			target.draw(text_num, states);
		}
};

