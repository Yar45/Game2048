#include "MenuCallable.h"

MenuCallable::MenuCallable(sf::Music* _musicList, sf::Sound* _soundList, size_t _currentMusicId,
	size_t _currentSoundId, size_t _musicNumber, size_t _soundNumber, ButtonAction* _action)
	: musicList(_musicList), soundList(_soundList), currentMusicId(_currentMusicId),
	currentSoundId(_currentSoundId), musicNumber(_musicNumber), soundNumber(_soundNumber), action(_action)
{}

MenuCallable::~MenuCallable() {
	for (size_t i = 0; i < musicNumber; ++i) {
		musicList[i].stop();
	}
	for (size_t i = 0; i < soundNumber; ++i) {
		soundList[i].stop();
		//delete soundList[i].getBuffer();
	}
	delete[] musicList;
	delete[] soundList;
}

void MenuCallable::startMenu() {
	changeGameMode(TO_START_MENU);
	setMusic(0);
}

void MenuCallable::endMenu() {
	changeGameMode(TO_END_MENU);
	setMusic(0);
}

void MenuCallable::startGame() {
	changeGameMode(TO_GAME);
	setMusic(2);
}

void MenuCallable::restartGame() {
	changeGameMode(RESTART_GAME);
	setMusic(2);
}

void MenuCallable::resizeGame(int height, int width) {
	if (width > 0 && height > 0) {
		BasicValues::WINDOW_previous_width = BasicValues::WINDOW_width;
		BasicValues::WINDOW_previous_height = BasicValues::WINDOW_height;

		//BasicValues::WINDOW_isFullscreen = false;
		BasicValues::WINDOW_width = width;
		BasicValues::WINDOW_height = height;
	}
	//else if (width == -1 && height == -1) {
	//	BasicValues::WINDOW_isFullscreen = true;
	//}
	changeGameMode(RESIZE_GAME);
	setMusic(2);
}

void MenuCallable::setMode(ButtonAction _action) {
	switch (_action)
	{
	case TO_START_MENU: {
		startMenu();
		break;
	}
	case TO_GAME: {
		startGame();
		break;
	}
	case TO_OPTIONS: {
		changeGameMode(TO_OPTIONS);
		break;
	}
	case TO_END_MENU: {
		endMenu();
		break;
	}
	case RESTART_GAME: {
		restartGame();
		break;
	}
	case RESIZE_GAME: {
		resizeGame(0, 0);
		break;
	}
	case RESIZE_400x300: {
		resizeGame(400, 300);
		break;
	}
	case RESIZE_640x480: {
		resizeGame(640, 480);
		break;
	}
	case RESIZE_800x600: {
		resizeGame(800, 600);
		break;
	}
						//case RESIZE_FULLSCREEN: {
						//	resizeGame(-1, -1);
						//	break;
						//}
	default:
		break;
	}
}

void MenuCallable::setVolume(float value) {
	for (size_t i = 0; i < musicNumber; ++i) {
		musicList[i].setVolume(100 * value);
	}
	for (size_t i = 0; i < soundNumber; ++i) {
		soundList[i].setVolume(100 * value);
	}
}

void MenuCallable::setMusic(size_t id) {
	musicList[currentMusicId].stop();
	currentMusicId = id;
	musicList[currentMusicId].play();
}

void MenuCallable::changeGameMode(ButtonAction _action) {
	*action = _action;
}
