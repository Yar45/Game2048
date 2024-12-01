#include "RectField.h"

RectField::RectField(unsigned int _sizeX, unsigned int _sizeY, unsigned int _cellSizeX, unsigned int _cellSizeY, unsigned int _cellCorner, unsigned int _fieldOffset, unsigned int _initCellsNumber) :
	sizeX(_sizeX), sizeY(_sizeY), cellSizeX(_cellSizeX), cellSizeY(_cellSizeY), cellCorner(_cellCorner), fieldOffset(_fieldOffset)
{
	border = new RoundedSquare(getSize().x, getSize().y, cellCorner);
	border->setFillColor(Colors::fieldBackground);

	field = new GameCell * *[sizeY];
	for (unsigned int j = 0; j < sizeY; ++j)
	{
		field[j] = new GameCell * [sizeX];
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

RectField::~RectField()
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

void RectField::getMaxResult() {
	std::ifstream file(SCORE_RESULT_PATH, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File was not opened" << std::endl;
		return;
	}
	file.read(reinterpret_cast<char*>(&maxScore), sizeof(size_t));
	file.close();
}

void RectField::saveIfMaximumResult() {
	bool res = std::filesystem::create_directory(SCORE_RESULT_FOLDER);

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
			maxScore = currentScore;
		}
		else {
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
				maxScore = currentScore;
			}
			else {
				maxScore = result;
				std::cout << "Score was less than max, not written: " << result << " > " << currentScore << std::endl;
			}
		}

		file.close();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		file.close();
	}
}

void RectField::restart(unsigned int _initCellsNumber) {
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

	std::cout << "SCORE: " << maxScore << std::endl;
	PrettySet::maxScoreLink->setString(std::to_string(maxScore));
	PrettySet::maxScoreLink->setOrigin(PrettySet::maxScoreLink->getGlobalBounds().getSize() / 2.f + PrettySet::maxScoreLink->getLocalBounds().getPosition());
	PrettySet::maxScoreLink->setPosition(BasicValues::SCORE_cellWidth + BasicValues::SCORE_cellOffset + PrettySet::maxScoreSquareLink->getGlobalBounds().getSize().x / 2.f, PrettySet::maxScoreSquareLink->getGlobalBounds().getSize().y * 0.6f);

	init(_initCellsNumber);
}

GameCell*** RectField::getField() const
{
	return field;
}

GameCell* RectField::getRandomFreePosition() const {
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

void RectField::init(unsigned int startCellCount) {
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

unsigned int RectField::moveLeft() {
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

bool RectField::moveLeftCheck() const {
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

unsigned int RectField::moveRight() {
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

bool RectField::moveRightCheck() const {
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

unsigned int RectField::moveDown() {
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

bool RectField::moveDownCheck() const {
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

unsigned int RectField::moveUp() {
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

bool RectField::moveUpCheck() const {
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

sf::Vector2f RectField::getFieldSize() const {
	return sf::Vector2f((cellSizeX + cellCorner) * sizeX, (cellSizeY + cellCorner) * sizeY);
}

sf::Vector2f RectField::getSize() const {
	return getFieldSize() + sf::Vector2f(fieldOffset, fieldOffset);
}

size_t RectField::getNumberFreePositions() const {
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

void RectField::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
