#include "RoundedSquare.h"

RoundedSquare::RoundedSquare(size_t _width, size_t _height, size_t _corner) : width(_width), height(_height), corner(_corner)
{
	if (corner > width / 2 || corner > height / 2) {
		corner = 0;
	}

	offsetWidth = width - corner * 2;
	offsetHeight = height - corner * 2;

	update();
}

size_t RoundedSquare::getPointCount() const
{
	return 32;
}

sf::Vector2f RoundedSquare::getPoint(size_t index) const
{
	float currentAngleRadian = index * 2 * PI / getPointCount() - PI / 2;
	float currentAngleDegree = 360.0f / getPointCount() * index;

	float x = std::cos(currentAngleRadian) * corner + corner;
	float y = std::sin(currentAngleRadian) * corner + corner;

	if (currentAngleDegree >= 0 && currentAngleDegree <= 180)
		x += offsetWidth;

	if (currentAngleDegree >= 90 && currentAngleDegree <= 270)
		y += offsetHeight;

	return sf::Vector2f(x, y);
}
