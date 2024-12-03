#pragma once

#include <fstream>			// „тение/запись файла/потока
#include <chrono>			// ¬рем€

#include <SFML/Graphics.hpp>// SFML библиотека дл€ графики
#include <SFML/Audio.hpp>	// SFML библиотека дл€ аудио

#include "RectField.h"		// ѕользовательский класс дл€ представлени€ игрового пол€ (сетки 4x4)
#include "StartMenu.h"		// ѕользовательский класс дл€ представлени€ начального меню
#include "EndMenu.h"		// ѕользовательский класс дл€ представлени€ меню итогов
#include "MenuCallable.h"	// ѕользовательский класс дл€ обработки событий кнопок
#include "Enums.h"			// —одержит перечислени€ (событи€ кнопки)
#include "Options.h"		// ѕользовательский класс дл€ представлени€ меню настроек
#include "Score.h"			// ѕользовательский класс дл€ представлени€ игрового счета
#include "PrettySet.h"      // ѕользовательский класс дл€ графических ресурсов
#include "BasicValues.h"    // ѕользовательский класс дл€ констант игры

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

