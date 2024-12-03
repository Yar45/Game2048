#pragma once

#include <SFML/Graphics.hpp>

#define OPACITY_CELL 220

using sf::Color;

class Colors
{
public:
	Colors() {}

	static inline const Color light_peach = { 255, 216, 177 };
	static inline const Color orange_peach = { 255, 204, 153 };
	static inline const Color corail_orange = { 255, 127, 80 };
	static inline const Color carrot = { 243, 98, 35 };
	static inline const Color pumpkin = { 255, 117, 24 };
	static inline const Color red_orange = { 201, 60, 32 };

	static inline const Color gameBackground = { 125, 198, 178 };
	static inline const Color fieldBackground = { 255, 255, 255, 150 };
	static inline const Color buttonBackground = { 139, 0, 255 };
	static inline const Color buttonBackgroundHover = { 160, 51, 255 };
	static inline const Color buttonBackgroundActive = { 109, 0, 204 };
	
	static inline const Color color_1 = { 231, 235, 238, OPACITY_CELL };
	static inline const Color color_2 = { 183, 188, 194, OPACITY_CELL };
	static inline const Color color_3 = { 142, 160, 160, OPACITY_CELL };
	static inline const Color color_4 = { 232, 191, 19, OPACITY_CELL };
	static inline const Color color_5 = { 237, 152, 30, OPACITY_CELL };
	static inline const Color color_6 = { 224, 122, 34, OPACITY_CELL };
	static inline const Color color_7 = { 205, 84, 40, OPACITY_CELL };
	static inline const Color color_8 = { 225, 74, 59, OPACITY_CELL };
	static inline const Color color_9 = { 200, 74, 74, OPACITY_CELL };
	static inline const Color color_10 = { 188, 56, 43, OPACITY_CELL };
	static inline const Color color_11 = { 124, 46, 51, OPACITY_CELL };
	static inline const Color color_12 = { 73, 124, 83, OPACITY_CELL };
};