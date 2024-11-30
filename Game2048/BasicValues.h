#pragma once

class BasicValues {
public:
	static inline const size_t GAME_win_number = 2048;
	static inline bool GAME_isWin = false;

	static inline unsigned int WINDOW_width = 480;
	static inline unsigned int WINDOW_height = 640;
	//static inline float WINDOW_scale = 1.f;
	//static inline bool WINDOW_isFullscreen = false;


	static inline unsigned int WINDOW_previous_width = 480;
	static inline unsigned int WINDOW_previous_height = 640;

	static inline size_t FIELD_rows = 4;
	static inline size_t FIELD_columns = 4;
	static inline size_t FIELD_cellWidth = 100;
	static inline size_t FIELD_cellHeight = 100;
	static inline size_t FIELD_cellCorner = 8;
	static inline size_t FIELD_cellOffset = 20;

	static inline size_t FIELD_cellNumberAtStart = 2;
	static inline size_t FIELD_cellNumberAtMove = 1;

	static inline unsigned int FIELD_cellFontSize = 18;


	static inline const size_t MUSIC_number = 4;
	static inline const size_t MUSIC_idAtStart = 0;
	static inline float  MUSIC_volumeAtStart = 0.1f;

	static inline const size_t SOUND_number = 1;
	static inline const size_t SOUND_idAtStart = 0;

	static inline size_t SCORE_cellWidth = 100;
	static inline size_t SCORE_cellHeight = 70;
	static inline size_t SCORE_cellCorner = 8;
	static inline size_t SCORE_cellOffset = 20;

	static inline unsigned int SCORE_fontSize = 16;

	static inline size_t GAME_menuButtonWidth = 70;
	static inline size_t GAME_menuButtonHeight = 70;
	static inline size_t GAME_menuButtonCorner = 8;

	static inline unsigned int BUTTON_fontSize = 18;

	static inline size_t MENU_buttonWidth = 200;
	static inline size_t MENU_buttonHeight = 100;
	static inline size_t MENU_buttonCorner = 8;
	static inline size_t MENU_buttonOffset = 100;
	static inline unsigned int MENU_fontSize = 22;


	static inline size_t OPTIONS_sliderWidth = 200;
	static inline size_t OPTIONS_sliderHeight = 10;
	static inline size_t OPTIONS_sliderCorner = 4;
	static inline size_t OPTIONS_sliderOffset = 100;
	static inline unsigned int OPTIONS_fontSize = 18;


	static void resizeValues() {
		float scale = (float)WINDOW_width / WINDOW_previous_width;

		FIELD_cellWidth *= scale;
		FIELD_cellHeight = FIELD_cellWidth;
		FIELD_cellOffset *= scale;

		FIELD_cellFontSize *= scale;

		SCORE_cellWidth *= scale;
		SCORE_cellHeight *= scale;
		SCORE_cellOffset *= scale;

		SCORE_fontSize *= scale;

		GAME_menuButtonWidth *= scale;
		GAME_menuButtonHeight *= scale;

		BUTTON_fontSize *= scale;

		MENU_buttonWidth *= scale;
		MENU_buttonHeight *= scale;
		MENU_buttonOffset *= scale;
		MENU_fontSize *= scale;

		OPTIONS_sliderWidth *= scale;
		OPTIONS_sliderOffset *= scale;

		OPTIONS_fontSize *= scale;
	}
};