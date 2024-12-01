#include "Score.h"

Score::Score(size_t _width, size_t _height, size_t _corner, size_t _scoreOffset, size_t currentScore, size_t maxScore)
	: currentScoreSq(_width, _height, _corner), maxScoreSq(_width, _height, _corner),
	width(_width), height(_height), corner(_corner), scoreOffset(_scoreOffset)
{
	currentScoreSq.setFillColor(Colors::color_1);
	maxScoreSq.setFillColor(Colors::color_1);

	currentScoreText.setFont(*PrettySet::font);
	currentScoreText.setFillColor(sf::Color::Black);
	currentScoreText.setOutlineColor(sf::Color::Black);
	currentScoreText.setCharacterSize(BasicValues::SCORE_fontSize);
	currentScoreText.setString(std::to_string(currentScore));
	currentScoreText.setOrigin(currentScoreText.getGlobalBounds().getSize() / 2.f + currentScoreText.getLocalBounds().getPosition());
	currentScoreText.setPosition(currentScoreSq.getGlobalBounds().getSize().x / 2.f, currentScoreSq.getGlobalBounds().getSize().y * 0.6f);

	maxScoreText.setFont(*PrettySet::font);
	maxScoreText.setFillColor(sf::Color::Black);
	maxScoreText.setOutlineColor(sf::Color::Black);
	maxScoreText.setCharacterSize(BasicValues::SCORE_fontSize);
	maxScoreText.setString(std::to_string(maxScore));
	maxScoreText.setOrigin(maxScoreText.getGlobalBounds().getSize() / 2.f + maxScoreText.getLocalBounds().getPosition());
	maxScoreText.setPosition(width + scoreOffset + maxScoreSq.getGlobalBounds().getSize().x / 2.f, maxScoreSq.getGlobalBounds().getSize().y * 0.6f);

	maxScoreSq.setPosition(width + scoreOffset, 0);

	currentScoreTextConst.setFont(*PrettySet::font);
	currentScoreTextConst.setFillColor(sf::Color::Black);
	currentScoreTextConst.setOutlineColor(sf::Color::Black);
	currentScoreTextConst.setCharacterSize(BasicValues::SCORE_fontSize);
	currentScoreTextConst.setString(L"—чет");
	currentScoreTextConst.setOrigin(currentScoreTextConst.getGlobalBounds().getSize() / 2.f + currentScoreTextConst.getLocalBounds().getPosition());
	currentScoreTextConst.setPosition(currentScoreSq.getGlobalBounds().getSize().x / 2.f, currentScoreSq.getGlobalBounds().getSize().y / 4.f);

	maxScoreTextConst.setFont(*PrettySet::font);
	maxScoreTextConst.setFillColor(sf::Color::Black);
	maxScoreTextConst.setOutlineColor(sf::Color::Black);
	maxScoreTextConst.setCharacterSize(BasicValues::SCORE_fontSize);
	maxScoreTextConst.setString(L"–екорд");
	maxScoreTextConst.setOrigin(maxScoreTextConst.getGlobalBounds().getSize() / 2.f + maxScoreTextConst.getLocalBounds().getPosition());
	maxScoreTextConst.setPosition(width + scoreOffset + maxScoreSq.getGlobalBounds().getSize().x / 2.f, maxScoreSq.getGlobalBounds().getSize().y / 4.f);

	PrettySet::setScoreLinks(&currentScoreText, &maxScoreText, &currentScoreSq, &maxScoreSq);
}

sf::Vector2f Score::getSize() {
	return sf::Vector2f(width + width + scoreOffset, height);
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(currentScoreSq, states);
	target.draw(currentScoreTextConst, states);
	target.draw(currentScoreText, states);
	target.draw(maxScoreSq, states);
	target.draw(maxScoreTextConst, states);
	target.draw(maxScoreText, states);
}
