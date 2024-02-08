#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Animator
{
public:
	Animator();
	void set(int frameCount, sf::RectangleShape* spritePtr);
	void set(int frameCount, sf::RectangleShape* spritePtr, std::string imgPath);

	void next();

private:
	sf::RectangleShape* spritePtr = nullptr;
	sf::IntRect rect;
	sf::Vector2i size;

	sf::Texture tex;

	int frameCount = 0, updatesPFrame = 15, currentFrame = 0;
};

