#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MenuCallable.h"
#include "PrettySet.h"

class EndMenu : public sf::Drawable, public sf::Transformable
{
public:
	sf::RenderWindow* window;
	MenuCallable* menuCallable;

	sf::Text currentScoreText;
	sf::Text currentScoreTextConst;
	sf::Text winText;
	Button* buttonRestart;

	size_t buttonWidth;
	size_t buttonHeight;
	size_t buttonCorner;
	size_t buttonOffset;
	size_t fontSize;

	float leftOffset;
	float upOffset1;
	float upOffset2;

	EndMenu(sf::RenderWindow* _window, MenuCallable* _menuCallable,
		size_t _buttonWidth, size_t _buttonHeight, size_t _buttonCorner, size_t _buttonOffset, size_t _fontSize) : 
		window(_window), menuCallable(_menuCallable), buttonWidth(_buttonWidth), buttonHeight(_buttonHeight),
		buttonCorner(_buttonCorner), buttonOffset(_buttonOffset), fontSize(_fontSize)
	{
		leftOffset = window->getSize().x / 2.f - buttonWidth / 2.f;
		upOffset1 = window->getSize().y / 2.f - buttonHeight - buttonOffset / 2.f;
		
		currentScoreTextConst.setFont(*PrettySet::font);
		currentScoreTextConst.setFillColor(sf::Color::White);
		currentScoreTextConst.setOutlineColor(sf::Color::White);
		currentScoreTextConst.setCharacterSize(fontSize);
		currentScoreTextConst.setString(L"Счет:");
		//currentScoreTextConst.setOrigin(currentScoreTextConst.getGlobalBounds().getSize() / 2.f + currentScoreTextConst.getLocalBounds().getPosition());
		currentScoreTextConst.setPosition(leftOffset, upOffset1);

		currentScoreText.setFont(*PrettySet::font);
		currentScoreText.setFillColor(sf::Color::White);
		currentScoreText.setOutlineColor(sf::Color::White);
		currentScoreText.setCharacterSize(fontSize);
		currentScoreText.setString("0");
		//currentScoreText.setOrigin(currentScoreText.getGlobalBounds().getSize() / 2.f + currentScoreText.getLocalBounds().getPosition());
		currentScoreText.setPosition(currentScoreTextConst.getPosition().x + currentScoreTextConst.getGlobalBounds().width + 40, upOffset1);

		winText.setFont(*PrettySet::font);
		winText.setFillColor(sf::Color::White);
		winText.setOutlineColor(sf::Color::White);
		winText.setCharacterSize(fontSize);
		winText.setString(L"Поражение");
		winText.setOrigin(winText.getGlobalBounds().getSize() / 2.f + winText.getLocalBounds().getPosition());
		winText.setPosition(window->getSize().x / 2.f, currentScoreText.getPosition().y + currentScoreText.getGlobalBounds().height + 40);

		upOffset2 = winText.getPosition().y + winText.getGlobalBounds().height + 10;

		buttonRestart = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"Рестарт", buttonWidth, buttonHeight, buttonCorner, menuCallable, RESTART_GAME);
		buttonRestart->setPosition(leftOffset, upOffset2);

		PrettySet::setScoreResultLinks(&currentScoreText, &currentScoreTextConst);
	}

	void setWin() {
		winText.setString(L"Победа");
		winText.setOrigin(winText.getGlobalBounds().getSize() / 2.f + winText.getLocalBounds().getPosition());
		winText.setPosition(window->getSize().x / 2.f, currentScoreText.getPosition().y + currentScoreText.getGlobalBounds().height + 40);
	}

	~EndMenu() {
		delete buttonRestart;
	}

	void updateMousePosition(float x, float y) {
		sf::Vector2f pos1 = buttonRestart->getPosition();
		bool b1 = buttonRestart->isPressed(x - pos1.x, y - pos1.y);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(currentScoreTextConst, states);
		target.draw(currentScoreText, states);
		target.draw(winText, states);
		target.draw(*buttonRestart, states);
	}
};

