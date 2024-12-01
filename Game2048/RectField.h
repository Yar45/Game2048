#pragma once

#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "GameCell.h"
#include "RoundedSquare.h"

#define SCORE_RESULT_FOLDER "data"
#define SCORE_RESULT_PATH "data/result.bin"

class RectField : public sf::Drawable, public sf::Transformable
{
	public:
		unsigned int cellSizeX;
		unsigned int cellSizeY;
		unsigned int cellCorner;

		unsigned int sizeX;
		unsigned int sizeY;
		GameCell*** field;

		unsigned int fieldOffset;

		RoundedSquare* border;

		unsigned int freeCellsNumber;

		size_t currentScore;
		size_t maxScore;

		RectField(unsigned int _sizeX, unsigned int _sizeY, unsigned int _cellSizeX, unsigned int _cellSizeY, 
			unsigned int _cellCorner, unsigned int _fieldOffset, unsigned int _initCellsNumber);

		~RectField();

		void getMaxResult();

		void saveIfMaximumResult();

		void restart(unsigned int _initCellsNumber);

		GameCell*** getField() const;

		GameCell* getRandomFreePosition() const;

		void init(unsigned int startCellCount);

		unsigned int moveLeft();

		bool moveLeftCheck() const;

		unsigned int moveRight();

		bool moveRightCheck() const;

		unsigned int moveDown();

		bool moveDownCheck() const;

		unsigned int moveUp();

		bool moveUpCheck() const;

		sf::Vector2f getFieldSize() const;

		sf::Vector2f getSize() const;

		size_t getNumberFreePositions() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};