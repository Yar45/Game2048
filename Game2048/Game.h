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

	Game(unsigned int fpsLimit, sf::RenderWindow* window) {
		currentFrame = 0;
		timeNow = std::chrono::system_clock::now();
		timeFrame = std::chrono::system_clock::now();
		elapsedTime = std::chrono::milliseconds(0);
		framePeriod = std::chrono::milliseconds(1000 / fpsLimit);
		this->fpsLimit = fpsLimit;

		this->window = window;
		rectField = new RectField(
			BasicValues::FIELD_rows, BasicValues::FIELD_columns,
			BasicValues::FIELD_cellWidth, BasicValues::FIELD_cellHeight,
			BasicValues::FIELD_cellCorner, BasicValues::FIELD_cellOffset,
			BasicValues::FIELD_cellNumberAtStart
		);

		rectField->setPosition((window->getSize().x - rectField->getSize().x) / 2.f, window->getSize().y - rectField->getSize().y - (window->getSize().x - rectField->getSize().x) / 2.f);
		
		sf::Music* musicList = initMusic();
		sf::Sound* soundList = initSounds();

		menuCallable = new MenuCallable(musicList, soundList, BasicValues::MUSIC_idAtStart, BasicValues::SOUND_idAtStart, BasicValues::MUSIC_number, BasicValues::SOUND_number, &action);
		menu = new StartMenu(window, menuCallable, BasicValues::MENU_buttonWidth, BasicValues::MENU_buttonHeight, BasicValues::MENU_buttonCorner, BasicValues::MENU_buttonOffset, BasicValues::MENU_fontSize);
		endMenu = new EndMenu(window, menuCallable, BasicValues::MENU_buttonWidth, BasicValues::MENU_buttonHeight, BasicValues::MENU_buttonCorner, BasicValues::MENU_buttonOffset, BasicValues::MENU_fontSize);

		options = new Options(window, menuCallable, BasicValues::MUSIC_volumeAtStart, BasicValues::OPTIONS_sliderWidth, BasicValues::OPTIONS_sliderHeight, BasicValues::OPTIONS_sliderCorner, BasicValues::OPTIONS_sliderOffset, BasicValues::OPTIONS_fontSize, BasicValues::MENU_buttonWidth, BasicValues::MENU_buttonHeight, BasicValues::MENU_buttonCorner, BasicValues::MENU_buttonOffset);

		score = new Score(BasicValues::SCORE_cellWidth, BasicValues::SCORE_cellHeight, BasicValues::SCORE_cellCorner, BasicValues::SCORE_cellOffset, 0, rectField->maxScore);
		score->setPosition(BasicValues::SCORE_cellOffset, BasicValues::SCORE_cellOffset);

		menuButton = new Button(
			PrettySet::font, PrettySet::texture, 
			PrettySet::textureSquareNormalPosition, PrettySet::textureSquareNormalPosition, PrettySet::textureSquareHoverPosition,
			L"Меню", BasicValues::GAME_menuButtonWidth, BasicValues::GAME_menuButtonHeight, BasicValues::GAME_menuButtonCorner, menuCallable, TO_START_MENU
		);
		menuButton->setPosition(window->getSize().x - menuButton->getSize().x - BasicValues::SCORE_cellOffset, BasicValues::SCORE_cellOffset);

		restartButton = new Button(
			PrettySet::font, PrettySet::texture,
			PrettySet::textureSquareNormalPosition, PrettySet::textureSquareNormalPosition, PrettySet::textureSquareHoverPosition,
			L"Рестарт", BasicValues::GAME_menuButtonWidth * 1.6f, BasicValues::GAME_menuButtonHeight, BasicValues::GAME_menuButtonCorner, menuCallable, RESTART_GAME
		);
		restartButton->setPosition(window->getSize().x - menuButton->getSize().x - restartButton->getSize().x - BasicValues::SCORE_cellOffset * 2, BasicValues::SCORE_cellOffset);

		spriteBackground.setTexture(*PrettySet::textureBackground1);
		float scale1 = (float)window->getSize().x / spriteBackground.getTextureRect().width;
		float scale2 = (float)window->getSize().y / spriteBackground.getTextureRect().height;
		float scaleCurrent = std::max(scale1, scale2);
		spriteBackground.setScale(scaleCurrent, scaleCurrent);

		menuCallable->startMenu();
	}

	~Game() {
		delete rectField;
		delete menu;
		delete endMenu;
		delete menuCallable;
		delete options;
		delete score;
		delete menuButton;
		delete restartButton;
	}

	sf::Music* initMusic() {
		sf::Music* musicList = new sf::Music[BasicValues::MUSIC_number];

		if (!musicList[0].openFromFile("assets/menu1-Sketchbook-2024-08-21.ogg"))
			std::cout << "Error loading menu1-Sketchbook-2024-08-21.ogg" << std::endl;
		if (!musicList[1].openFromFile("assets/menu2-horror-Sketchbook-2024-08-13.ogg"))
			std::cout << "Error loading menu2-horror-Sketchbook-2024-08-13.ogg" << std::endl;
		if (!musicList[2].openFromFile("assets/game1-Sketchbook-2024-10-30.ogg"))
			std::cout << "Error loading game1-Sketchbook-2024-10-30.ogg" << std::endl;
		if (!musicList[3].openFromFile("assets/game2-Sketchbook-2024-08-01.ogg"))
			std::cout << "Error loading game2-Sketchbook-2024-08-01.ogg" << std::endl;

		for (unsigned int i = 0; i < BasicValues::MUSIC_number; ++i) {
			musicList[i].setLoop(true);
			musicList[i].setVolume(BasicValues::MUSIC_volumeAtStart);
		}

		static_assert(BasicValues::MUSIC_number == 4, "При изменении MUSIC_NUMBER необходимо добавить выше сами звуки");
		return musicList;
	}

	sf::Sound* initSounds() {
		sf::Sound* soundList = new sf::Sound[BasicValues::SOUND_number];
		sf::SoundBuffer* soundBuffers = new sf::SoundBuffer[BasicValues::SOUND_number];

		if (!soundBuffers[0].loadFromFile("assets/tuturu.ogg"))
			std::cout << "Error loading tuturu.ogg" << std::endl;

		for (unsigned int i = 0; i < BasicValues::SOUND_number; ++i) {
			soundList[i].setBuffer(soundBuffers[i]);
			soundList[i].setLoop(false);
			soundList[i].setVolume(BasicValues::MUSIC_volumeAtStart);
		}

		static_assert(BasicValues::SOUND_number == 1, "При изменении SOUND_NUMBER необходимо добавить выше сами звуки");
		return soundList;
	}

	void loop() {
		timeNow = std::chrono::system_clock::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeFrame);

		if (elapsedTime >= framePeriod) {
			timeFrame = std::chrono::system_clock::now();
			currentFrame += 1;

			if (currentFrame >= fpsLimit) {
				currentFrame = 0;
			}

			window->draw(spriteBackground);

			switch (action)
			{
			case TO_START_MENU: {
				mousePosition = sf::Mouse::getPosition(*window);

				menu->updateMousePosition(mousePosition.x, mousePosition.y);

				//window->clear(Colors::gameBackground);
				window->draw(*menu);
				break;
			}

			case TO_GAME: {
				mousePosition = sf::Mouse::getPosition(*window);

				sf::Vector2f pos1 = menuButton->getPosition();
				sf::Vector2f pos2 = restartButton->getPosition();
				menuButton->isPressed(mousePosition.x - pos1.x, mousePosition.y - pos1.y);
				restartButton->isPressed(mousePosition.x - pos2.x, mousePosition.y - pos2.y);

				//window->clear(Colors::gameBackground);
				window->draw(*menuButton);
				window->draw(*restartButton);
				window->draw(*score);
				window->draw(*rectField);

				if (BasicValues::GAME_isWin == true) {
					endMenu->setWin();
					PrettySet::currentScoreResultLink->setString(std::to_string(rectField->currentScore));
					menuCallable->soundList[0].play();
					action = TO_END_MENU;
				}

				break;
			}

			case TO_OPTIONS: {
				mousePosition = sf::Mouse::getPosition(*window);

				options->updateMousePosition(mousePosition.x, mousePosition.y);

				sf::Vector2f pos1 = menuButton->getPosition();
				menuButton->isPressed(mousePosition.x - pos1.x, mousePosition.y - pos1.y);

				//window->clear(Colors::gameBackground);
				window->draw(*menuButton);
				window->draw(*options);
				break;
			}

			case TO_END_MENU: {
				mousePosition = sf::Mouse::getPosition(*window);

				endMenu->updateMousePosition(mousePosition.x, mousePosition.y);

				window->draw(*endMenu);
				break;
			}

			case RESTART_GAME: {
				window->draw(*menuButton);
				window->draw(*restartButton);
				window->draw(*score);
				window->draw(*rectField);

				rectField->restart(BasicValues::FIELD_cellNumberAtStart);

				menuCallable->setMode(TO_GAME);
				break;
			}

			case RESIZE_GAME: {
				window->setSize(sf::Vector2u(window->getSize().x, window->getSize().y-1));
				break;
			}

			default:
				break;
			}

			window->display();
		}
	}

	void onKeyboard(const sf::Keyboard::Key& button) {
		if (action == TO_GAME) {
			unsigned int moves = 0;
			switch (button)
			{
			case sf::Keyboard::Key::Left:
				moves = rectField->moveLeft();
				break;
			case sf::Keyboard::Key::Right:
				moves = rectField->moveRight();
				break;
			case sf::Keyboard::Key::Up:
				moves = rectField->moveUp();
				break;
			case sf::Keyboard::Key::Down:
				moves = rectField->moveDown();
				break;
			default:
				break;
			}

			if (moves == 0) {
				//std::cout << "0 moves" << std::endl;
				if (!(rectField->moveLeftCheck() || rectField->moveRightCheck() || rectField->moveUpCheck() || rectField->moveDownCheck())) {
					//std::cout << "No moves available" << std::endl;
					
					PrettySet::currentScoreResultLink->setString(std::to_string(rectField->currentScore));

					if (BasicValues::GAME_isWin == true) {
						endMenu->setWin();
					}

					menuCallable->soundList[0].play();
					
					action = TO_END_MENU;
				}
			} else {
				//std::cout << moves << " moves" << std::endl;
				rectField->init(BasicValues::FIELD_cellNumberAtMove);
			}
		}
	}

private:
	std::chrono::system_clock::time_point timeNow;
	std::chrono::system_clock::time_point timeFrame;
	std::chrono::milliseconds elapsedTime;
	std::chrono::milliseconds framePeriod;

	sf::Vector2i mousePosition;

	sf::Sprite spriteBackground;
};

