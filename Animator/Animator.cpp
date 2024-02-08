#include "Animator.h"

Animator::Animator()
{
}

void Animator::set(int frameCount, sf::RectangleShape* spritePtr)
{
	// I needed to slow down the framerate, 30/s was too much
	// Uses updates per frame
	this->frameCount = frameCount * updatesPFrame;
	this->spritePtr = spritePtr;
	if (spritePtr != nullptr)
	{
		size = sf::Vector2i(spritePtr->getSize());
		rect = sf::IntRect(sf::Vector2i(), size);
		spritePtr->setTextureRect(rect);
	}
}

void Animator::set(int frameCount, sf::RectangleShape* spritePtr, std::string imgPath)
{
	// I needed to slow down the framerate, 30/s was too much	
	// Uses updates per frame
	this->frameCount = frameCount * updatesPFrame;
	this->spritePtr = spritePtr;
	if (spritePtr != nullptr)
	{
		size = sf::Vector2i(spritePtr->getSize());
		rect = sf::IntRect(sf::Vector2i(), size);
		tex.loadFromFile(imgPath);
		spritePtr->setTexture(&tex);
		spritePtr->setTextureRect(rect);
	}
}

void Animator::next()
{
	// Increases the image rectangle by its height and loops back when it reaches the end
	if (spritePtr != nullptr)
	{
		currentFrame++;
		if (currentFrame >= frameCount)
			currentFrame -= frameCount;

		// the dividing to an int is needed for the updates per frame delay.
		rect.top = (currentFrame / updatesPFrame) * size.y;
		spritePtr->setTextureRect(rect);
	}
}
