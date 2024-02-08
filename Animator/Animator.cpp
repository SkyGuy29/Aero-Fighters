#include "Animator.h"

Animator::Animator()
{
}

void Animator::set(int frameCount, sf::RectangleShape* spritePtr)
{
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
	if (spritePtr != nullptr)
	{
		currentFrame++;
		if (currentFrame >= frameCount)
			currentFrame -= frameCount;

		rect.top = (currentFrame / updatesPFrame) * size.y;
		spritePtr->setTextureRect(rect);
	}
}
