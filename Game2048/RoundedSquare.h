#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class RoundedSquare : public sf::Shape 
{
	private:
		size_t width;
		size_t height;
		size_t corner;
		size_t offsetWidth;
		size_t offsetHeight;

		const double PI = 3.141592653589793;
		
	public:
		RoundedSquare(size_t _width, size_t _height, size_t _corner);

		virtual size_t getPointCount() const;

		virtual sf::Vector2f getPoint(size_t index) const;
};

