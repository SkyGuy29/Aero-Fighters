#pragma once

#include <SFML/Graphics.hpp>

class Animator
{
public:
	Animator();
	void set(int frameCount, sf::RectangleShape* spritePtr);

	void next();

private:
	sf::RectangleShape* spritePtr = nullptr;
	sf::IntRect rect;
	sf::Vector2f size;

	int frameCount = 0, currentFrame = 0;
};

