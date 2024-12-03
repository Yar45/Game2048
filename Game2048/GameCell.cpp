#include "GameCell.h"

GameCell::GameCell(size_t _cellLength, size_t _cellCorner, long long _num) : sq(_cellLength, _cellLength, _cellCorner), num(_num) {
	text_num.setFont(*PrettySet::font);
	text_num.setFillColor(sf::Color::Black);
	text_num.setOutlineColor(sf::Color::Black);
	text_num.setCharacterSize(BasicValues::FIELD_cellFontSize);
	if (num != 0)
		text_num.setString(std::to_string(num));

	text_num.setOrigin(text_num.getGlobalBounds().getSize() / 2.f + text_num.getLocalBounds().getPosition());
	text_num.setPosition(sq.getGlobalBounds().getSize() / 2.f);

	sq.setFillColor(Colors::color_1);
}

GameCell::~GameCell()
{
}

void GameCell::setNum(long long num) {
	this->num = num;
	if (num != 0) {
		text_num.setString(std::to_string(num));
		text_num.setOrigin(text_num.getGlobalBounds().getSize() / 2.f + text_num.getLocalBounds().getPosition());
		text_num.setPosition(sq.getGlobalBounds().getSize() / 2.f);
	}
	else {
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

long long GameCell::getNum() const {
	return num;
}

GameCell& GameCell::operator = (unsigned int _num) {
	num = _num;
	return *this;
}

GameCell& GameCell::operator = (const GameCell& cell) {
	num = cell.num;
	return *this;
}

GameCell& GameCell::operator * (unsigned int _num) {
	num *= _num;
	return *this;
}

bool GameCell::operator == (unsigned int _num) {
	return num == _num;
}

bool GameCell::operator == (const GameCell& cell) {
	return num == cell.num;
}

bool GameCell::operator != (unsigned int _num) {
	return num != _num;
}

bool GameCell::operator != (const GameCell& cell) {
	return num != cell.num;
}

void GameCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sq, states);
	target.draw(text_num, states);
}

