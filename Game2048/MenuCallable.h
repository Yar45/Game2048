#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "Enums.h"
#include "BasicValues.h"

class MenuCallable {
public:
	sf::Music* musicList;
	sf::Sound* soundList;
	size_t currentMusicId;
	size_t currentSoundId;
	size_t musicNumber;
	size_t soundNumber;

	ButtonAction* action;

	MenuCallable(sf::Music* _musicList, sf::Sound* _soundList, size_t _currentMusicId,
		size_t _currentSoundId, size_t _musicNumber, size_t _soundNumber, ButtonAction* _action);

	~MenuCallable();

	void startMenu();

	void endMenu();

	void startGame();

	void restartGame();

	void resizeGame(int height, int width);

	void setMode(ButtonAction _action);

	void setVolume(float value);

private:
	void setMusic(size_t id);

	void changeGameMode(ButtonAction _action);
};