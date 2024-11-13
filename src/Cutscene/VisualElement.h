#pragma once
#include <Math.h>
#include <SFML/Graphics.hpp>

template<typename ElementType>
class VisualElement
{
public:
	VisualElement() = delete;

	VisualElement(sf::Vector2f pointA, sf::Vector2f pointB, ElementType element, bool doesFlash, unsigned char flashTime = 0) :
		pointA(pointA), pointB(pointB), element(element), baseFlashLength(flashTime), flashFlags(doesFlash << 7) {}

	void tick(unsigned short time)
	{
		float dy, dx;

		if (spawnTime <= time)
		{
			if (pointB.x < pointA.x) // If point b is to the left of point a
			{
				dy = (pointA.y - pointB.y);
				dx = (pointA.x - pointB.x);
			}
			else
			{
				dy = (pointB.y - pointA.y);
				dx = (pointB.x - pointA.x);
			}

			pos.x += dx * speed;
			pos.y += dy * speed;

			if ((flashFlags & 0b10000000) && (flashFlags & 0b00111111) == 0)
				flashFlags = ((~flashFlags) & 0b11000000) | 0b10000000;

			flashFlags += 1;

		}

	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(element);
	}
	ElementType getElement() { return element; }

private:
	// The element that this handles
	ElementType element;

	// The starting position of the element
	sf::Vector2f pointA;
	// The ending position of the element
	sf::Vector2f pointB;
	// The position on screen of the element
	sf::Vector2f pos;

	// The number of ticks before this element spawns
	unsigned short spawnTime;

	// The speed at which it moves from Point A to Point B
	unsigned short speed;

	// MSB = isFlashing,
	// 1 to the right of the MSB = flashState; 0 = false, 1 = true
	// 6 LSB = State length
	unsigned char flashFlags;

	// The default flash length for this element
	unsigned char baseFlashLength;
};

