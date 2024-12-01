#pragma once

#include <fstream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "RectField.h"
#include "StartMenu.h"
#include "EndMenu.h"
#include "MenuCallable.h"
#include "Enums.h"
#include "Options.h"
#include "Score.h"
#include "PrettySet.h"
#include "BasicValues.h"

class Game
{
public:
	unsigned int currentFrame;
	unsigned int fpsLimit; // V-SYNC Limit

	ButtonAction action = TO_START_MENU;

	sf::RenderWindow* window;
	RectField* rectField;

	StartMenu* menu;
	EndMenu* endMenu;
	MenuCallable* menuCallable;

	Options* options;
	Score* score;
	Button* menuButton;
	Button* restartButton;

	Game(unsigned int fpsLimit, sf::RenderWindow* window);

	~Game();

	sf::Music* initMusic();

	sf::Sound* initSounds();

	void loop();

	void onKeyboard(const sf::Keyboard::Key& button);

private:
	std::chrono::system_clock::time_point timeNow;
	std::chrono::system_clock::time_point timeFrame;
	std::chrono::milliseconds elapsedTime;
	std::chrono::milliseconds framePeriod;

	sf::Vector2i mousePosition;

	sf::Sprite spriteBackground;
};

