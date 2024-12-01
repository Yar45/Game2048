#include "StartMenu.h"

StartMenu::StartMenu(sf::RenderWindow* _window, MenuCallable* _menuCallable,
	size_t _buttonWidth, size_t _buttonHeight, size_t _buttonCorner, size_t _buttonOffset, size_t _fontSize) :
	window(_window), menuCallable(_menuCallable), buttonWidth(_buttonWidth), buttonHeight(_buttonHeight),
	buttonCorner(_buttonCorner), buttonOffset(_buttonOffset)
{
	leftOffset = window->getSize().x / 2.f - buttonWidth / 2.f;
	upOffset1 = window->getSize().y / 2.f - buttonHeight - buttonOffset / 2.f;
	upOffset2 = window->getSize().y / 2.f - buttonHeight + buttonOffset;

	buttonStart = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"Начать игру", buttonWidth, buttonHeight, buttonCorner, menuCallable, TO_GAME);
	buttonStart->setPosition(leftOffset, upOffset1);

	buttonOptions = new Button(PrettySet::font, PrettySet::texture, PrettySet::textureNormalPosition2, PrettySet::textureNormalPosition2, PrettySet::textureHoverPosition2, L"Настройки", buttonWidth, buttonHeight, buttonCorner, menuCallable, TO_OPTIONS);
	buttonOptions->setPosition(leftOffset, upOffset2);
}

StartMenu::~StartMenu() {
	delete buttonStart;
	delete buttonOptions;
}

void StartMenu::updateMousePosition(float x, float y) {
	sf::Vector2f pos1 = buttonStart->getPosition();
	sf::Vector2f pos2 = buttonOptions->getPosition();
	bool b1 = buttonStart->isPressed(x - pos1.x, y - pos1.y);
	bool b2 = buttonOptions->isPressed(x - pos2.x, y - pos2.y);
}

void StartMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*buttonStart, states);
	target.draw(*buttonOptions, states);
}
