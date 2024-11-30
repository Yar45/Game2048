#pragma once

#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "GameCell.h"
#include "RoundedSquare.h"

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

		RectField(unsigned int _sizeX, unsigned int _sizeY, unsigned int _cellSizeX, unsigned int _cellSizeY, unsigned int _cellCorner, unsigned int _fieldOffset, unsigned int _initCellsNumber):
			sizeX(_sizeX), sizeY(_sizeY), cellSizeX(_cellSizeX), cellSizeY(_cellSizeY), cellCorner(_cellCorner), fieldOffset(_fieldOffset)
		{
			border = new RoundedSquare(getSize().x, getSize().y, cellCorner);
			border->setFillColor(Colors::fieldBackground);

			field = new GameCell **[sizeY];
			for (unsigned int j = 0; j < sizeY; ++j)
			{
				field[j] = new GameCell*[sizeX];
				for (unsigned int i = 0; i < sizeX; ++i)
				{
					field[j][i] = new GameCell(cellSizeX, cellCorner, 0);
					field[j][i]->setPosition((cellSizeX + cellCorner) * i + fieldOffset * 2 / 3, (cellSizeY + cellCorner) * j + fieldOffset * 2 / 3);
					//field[j][i]->text_num.setString(std::to_string(j) + " " + std::to_string(i));
				}
			}
			freeCellsNumber = sizeX * sizeY;

			getMaxResult();

			init(_initCellsNumber);
		}

		~RectField()
		{
			for (unsigned int i = 0; i < sizeY; ++i)
			{
				for (unsigned int j = 0; j < sizeX; ++j)
				{
					delete field[i][j];
				}
				delete[] field[i];
			}
			delete[] field;
			delete border;
		}

		void getMaxResult() {
			std::ifstream file(SCORE_RESULT_PATH, std::ios::binary);
			if (!file.is_open())
			{
				std::cout << "File was not opened" << std::endl;
				return;
			}
			file.read(reinterpret_cast<char*>(&maxScore), sizeof(size_t));
			file.close();
		}

		void saveIfMaximumResult() {
			std::fstream file;
			try {
				if (!std::filesystem::exists(SCORE_RESULT_PATH)) {
					std::cout << "File is not exists, trying to create" << std::endl;
					file.open(SCORE_RESULT_PATH, std::ios::binary | std::ios::out);

					if (!file.is_open())
					{
						throw std::exception("Unable to create file");
					}
					std::cout << "Score was written" << std::endl;
					file.write(reinterpret_cast<const char*>(&currentScore), sizeof(size_t));
					if (!file.good()) { // Проверка на ошибки записи
						throw std::exception("Error writing file");
					}
				} else {
					std::cout << "Trying to open file" << std::endl;
					file.open(SCORE_RESULT_PATH, std::ios::binary | std::ios::in | std::ios::out);

					if (!file.is_open())
					{
						throw std::exception("Unable to open file");
					}

					size_t result = 0;
					file.read(reinterpret_cast<char*>(&result), sizeof(result));
					if (!file.good()) { // Проверка на ошибки чтения
						throw std::exception("Error reading file");
					}

					// Перемещаем указатель файла в начало перед записью.
					file.seekp(0, std::ios::beg);

					if (result < currentScore) {
						file.write(reinterpret_cast<const char*>(&currentScore), sizeof(size_t));
						if (!file.good()) { // Проверка на ошибки записи
							throw std::exception("Error writing file");
						}
						std::cout << "Score was written: " << currentScore << std::endl;
					} else {
						std::cout << "Score was less than max, not written: " << result << " > " << currentScore << std::endl;
					}
				}

				file.close();
			} catch (std::exception ex) {
				std::cout << ex.what() << std::endl;
				file.close();
			}
		}

		void restart(unsigned int _initCellsNumber) {
			for (unsigned int i = 0; i < sizeY; ++i)
			{
				for (unsigned int j = 0; j < sizeX; ++j)
				{
					field[i][j]->setNum(0);
				}
			}

			freeCellsNumber = sizeX * sizeY;

			saveIfMaximumResult();
			currentScore = 0;
			BasicValues::GAME_isWin = false;

			PrettySet::currentScoreLink->setString("0");
			PrettySet::currentScoreLink->setOrigin(PrettySet::currentScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::currentScoreLink->getLocalBounds().getPosition());
			PrettySet::currentScoreLink->setPosition(PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);

			init(_initCellsNumber);
		}

		GameCell*** getField() const
		{
			return field;
		}

		GameCell * getRandomFreePosition() const {
			if (freeCellsNumber == 0)
				return nullptr;

			int x = rand() % sizeX;
			int y = rand() % sizeY;
			while (field[x][y]->getNum() != 0) {
				x = rand() % sizeX;
				y = rand() % sizeY;
			}
			return field[x][y];
		}

		void init(unsigned int startCellCount) {
			GameCell* cell;
			for (unsigned int i = 0; i < startCellCount; ++i) {
				cell = getRandomFreePosition();
				if (cell != nullptr) {
					cell->setNum(2);

					freeCellsNumber -= 1;
					//std::cout << "Cells: " << freeCellsNumber << "\n";
				}
			}
		}

		unsigned int moveLeft() {
			using namespace std::chrono_literals;

			unsigned int moves = 0;

			//std::cout << "Moving left" << std::endl;
			for (unsigned int y = 0; y < sizeY; ++y)
			{
				int pos = 0;
				for (int i = 0; i < sizeX; i++) {
					if (field[y][i]->getNum() != 0) {
						field[y][pos]->setNum(field[y][i]->getNum());
						if (pos != i) {
							field[y][i]->setNum(0);

							moves++;
						}
						pos++;
					}
				}

				// Второй проход: объединяем одинаковые значения по соседству
				for (unsigned int i = 0; i < sizeY - 1; ++i) {
					long long current = field[y][i]->getNum();
					long long next = field[y][i + 1]->getNum();
					if (current != 0 && current == next) {
						field[y][i]->setNum(current * 2); // Удваиваем текущее значение
						field[y][i + 1]->setNum(0); // Обнуляем следующую ячейку
						currentScore += current * 2;
						freeCellsNumber += 1;

						moves++;
					}
				}

				pos = 0;
				for (unsigned int i = 0; i < sizeX; ++i) {
					if (field[y][i]->getNum() == BasicValues::GAME_win_number) {
						BasicValues::GAME_isWin = true;
					}

					if (field[y][i]->getNum() != 0) {
						field[y][pos]->setNum(field[y][i]->getNum());
						if (pos != i) {
							field[y][i]->setNum(0);

							moves++;
						}
						pos++;
						std::this_thread::sleep_for(5ms);
					}
				}
			}
			if (PrettySet::currentScoreLink != nullptr) {
				PrettySet::currentScoreLink->setString(std::to_string(currentScore));
				PrettySet::currentScoreLink->setOrigin(PrettySet::currentScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::currentScoreLink->getLocalBounds().getPosition());
				PrettySet::currentScoreLink->setPosition(PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);
			}

			return moves;
		}

		bool moveLeftCheck() const {
			//std::cout << "Checking moves left" << std::endl;
			for (unsigned int y = 0; y < sizeY; ++y) {
				int pos = 0;
				for (int i = 0; i < sizeX; i++) {
					if (field[y][i]->getNum() != 0) {
						if (pos != i) {
							return true;
						}
						pos++;
					}
				}

				// Проверка на объединение
				for (unsigned int i = 0; i < sizeX - 1; ++i) {
					if (field[y][i]->getNum() != 0 && field[y][i]->getNum() == field[y][i + 1]->getNum()) {
						return true;
					}
				}
			}

			return false;
		}

		unsigned int moveRight() {
			using namespace std::chrono_literals;

			unsigned int moves = 0;

			//std::cout << "Moving right" << std::endl;
			for (unsigned int y = 0; y < sizeY; ++y) {
				int pos = sizeX - 1;
				for (int i = sizeX - 1; i >= 0; --i) {
					if (field[y][i]->getNum() != 0) {
						field[y][pos]->setNum(field[y][i]->getNum());
						if (pos != i) {
							field[y][i]->setNum(0);

							moves++;
						}
						pos--;
					}
				}

				// Второй проход: объединяем одинаковые значения по соседству
				for (int i = sizeX - 1; i > 0; --i) {
					long long current = field[y][i]->getNum();
					long long next = field[y][i - 1]->getNum();
					if (current != 0 && current == next) {
						field[y][i]->setNum(current * 2); // Удваиваем текущее значение
						field[y][i - 1]->setNum(0); // Обнуляем предыдущую ячейку
						currentScore += current * 2;
						freeCellsNumber += 1;

						moves++;
					}
				}

				pos = sizeX - 1;
				for (int i = sizeX - 1; i >= 0; --i) {
					if (field[y][i]->getNum() == BasicValues::GAME_win_number) {
						BasicValues::GAME_isWin = true;
					}

					if (field[y][i]->getNum() != 0) {
						field[y][pos]->setNum(field[y][i]->getNum());
						if (pos != i) {
							field[y][i]->setNum(0);

							moves++;
						}
						pos--;
						std::this_thread::sleep_for(5ms);
					}
				}
			}
			if (PrettySet::currentScoreLink != nullptr) {
				PrettySet::currentScoreLink->setString(std::to_string(currentScore));
				PrettySet::currentScoreLink->setOrigin(PrettySet::currentScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::currentScoreLink->getLocalBounds().getPosition());
				PrettySet::currentScoreLink->setPosition(PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);
			}

			return moves;
		}

		bool moveRightCheck() const {
			//std::cout << "Checking moves right" << std::endl;
			for (unsigned int y = 0; y < sizeY; ++y) {
				int pos = sizeX - 1;
				for (int i = sizeX - 1; i >= 0; --i) {
					if (field[y][i]->getNum() != 0) {
						if (pos != i) {
							return true;
						}
						pos--;
					}
				}

				// Проверка на объединение
				for (int i = sizeX - 1; i > 0; --i) {
					if (field[y][i]->getNum() != 0 && field[y][i]->getNum() == field[y][i - 1]->getNum()) {
						return true;
					}
				}
			}

			return false;
		}

		unsigned int moveDown() {
			using namespace std::chrono_literals;

			unsigned int moves = 0;

			//std::cout << "Moving down" << std::endl;
			for (unsigned int x = 0; x < sizeX; ++x) {
				int pos = sizeY - 1;
				for (int i = sizeY - 1; i >= 0; --i) {
					if (field[i][x]->getNum() != 0) {
						field[pos][x]->setNum(field[i][x]->getNum());
						if (pos != i) {
							field[i][x]->setNum(0);

							moves++;
						}
						pos--;
					}
				}

				// Второй проход: объединяем одинаковые значения по соседству
				for (int i = sizeY - 1; i > 0; --i) {
					long long current = field[i][x]->getNum();
					long long next = field[i - 1][x]->getNum();
					if (current != 0 && current == next) {
						field[i][x]->setNum(current * 2); // Удваиваем текущее значение
						field[i - 1][x]->setNum(0); // Обнуляем предыдущую ячейку
						currentScore += current * 2;
						freeCellsNumber += 1;

						moves++;
					}
				}

				pos = sizeY - 1;
				for (int i = sizeY - 1; i >= 0; --i) {
					if (field[i][x]->getNum() == BasicValues::GAME_win_number) {
						BasicValues::GAME_isWin = true;
					}

					if (field[i][x]->getNum() != 0) {
						field[pos][x]->setNum(field[i][x]->getNum());
						if (pos != i) {
							field[i][x]->setNum(0);

							moves++;
						}
						pos--;
						std::this_thread::sleep_for(5ms);
					}
				}
			}
			if (PrettySet::currentScoreLink != nullptr) {
				PrettySet::currentScoreLink->setString(std::to_string(currentScore));
				PrettySet::currentScoreLink->setOrigin(PrettySet::currentScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::currentScoreLink->getLocalBounds().getPosition());
				PrettySet::currentScoreLink->setPosition(PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);
			}

			return moves;
		}

		bool moveDownCheck() const {
			//std::cout << "Checking moves down" << std::endl;
			for (unsigned int x = 0; x < sizeX; ++x) {
				int pos = sizeY - 1;
				for (int i = sizeY - 1; i >= 0; --i) {
					if (field[i][x]->getNum() != 0) {
						if (pos != i) {
							return true;
						}
						pos--;
					}
				}

				// Проверка на объединение
				for (int i = sizeY - 1; i > 0; --i) {
					if (field[i][x]->getNum() != 0 && field[i][x]->getNum() == field[i - 1][x]->getNum()) {
						return true;
					}
				}
			}

			return false;
		}

		unsigned int moveUp() {
			using namespace std::chrono_literals;

			unsigned int moves = 0;

			//std::cout << "Moving up" << std::endl;
			for (unsigned int x = 0; x < sizeX; ++x) {
				int pos = 0;
				for (int i = 0; i < sizeY; ++i) {
					if (field[i][x]->getNum() != 0) {
						field[pos][x]->setNum(field[i][x]->getNum());
						if (pos != i) {
							field[i][x]->setNum(0);

							moves++;
						}
						pos++;
					}
				}

				// Второй проход: объединяем одинаковые значения по соседству
				for (unsigned int i = 0; i < sizeY - 1; ++i) {
					long long current = field[i][x]->getNum();
					long long next = field[i + 1][x]->getNum();
					if (current != 0 && current == next) {
						field[i][x]->setNum(current * 2); // Удваиваем текущее значение
						field[i + 1][x]->setNum(0); // Обнуляем следующую ячейку
						currentScore += current * 2;
						freeCellsNumber += 1;

						moves++;
					}
				}

				pos = 0;
				for (unsigned int i = 0; i < sizeY; ++i) {
					if (field[i][x]->getNum() == BasicValues::GAME_win_number) {
						BasicValues::GAME_isWin = true;
					}

					if (field[i][x]->getNum() != 0) {
						field[pos][x]->setNum(field[i][x]->getNum());
						if (pos != i) {
							field[i][x]->setNum(0);

							moves++;
						}
						pos++;
						std::this_thread::sleep_for(5ms);
					}
				}
			}
			if (PrettySet::currentScoreLink != nullptr) {
				PrettySet::currentScoreLink->setString(std::to_string(currentScore));
				PrettySet::currentScoreLink->setOrigin(PrettySet::currentScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::currentScoreLink->getLocalBounds().getPosition());
				PrettySet::currentScoreLink->setPosition(PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::currentScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);
			}

			return moves;
		}

		bool moveUpCheck() const {
			//std::cout << "Checking moves up" << std::endl;
			for (unsigned int x = 0; x < sizeX; ++x) {
				int pos = 0;
				for (int i = 0; i < sizeY; ++i) {
					if (field[i][x]->getNum() != 0) {
						if (pos != i) {
							return true;
						}
						pos++;
					}
				}

				// Проверка на объединение
				for (unsigned int i = 0; i < sizeY - 1; ++i) {
					if (field[i][x]->getNum() != 0 && field[i][x]->getNum() == field[i + 1][x]->getNum()) {
						return true;
					}
				}
			}

			return false;
		}

		sf::Vector2f getFieldSize() const {
			return sf::Vector2f((cellSizeX + cellCorner) * sizeX, (cellSizeY + cellCorner) * sizeY);
		}

		sf::Vector2f getSize() const {
			return getFieldSize() + sf::Vector2f(fieldOffset, fieldOffset);
		}

		size_t getNumberFreePositions() const {
			size_t number = 0;
			for (unsigned int y = 0; y < sizeY; ++y)
			{
				for (unsigned int i = 0; i < sizeX; i++) {
					if (field[y][i]->getNum() == 0) {
						++number;
					}
				}
			}
			return number;
		}

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();

			target.draw(*border, states);
			for (unsigned int i = 0; i < sizeY; ++i)
			{
				for (unsigned int j = 0; j < sizeX; ++j)
				{
					target.draw(*field[i][j], states);
				}
			}
		}
};