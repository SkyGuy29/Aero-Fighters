#include "Animator.h"

Animator::Animator()
{
}

void Animator::set(int frameCount, sf::RectangleShape* spritePtr)
{
	this->frameCount = frameCount;
	this->spritePtr = spritePtr;
	if (spritePtr != nullptr)
	{
		size = spritePtr->getSize();
		rect.width = size.x;
		rect.height = size.y;
		rect.left = 0;
		rect.top = 0;
	}
}

void Animator::next()
{
	if (spritePtr != nullptr)
	{
		currentFrame++;
		if (currentFrame >= frameCount)
			currentFrame -= frameCount;

		rect.top = currentFrame * size.y;
		spritePtr->setTextureRect(rect);
	}
}
