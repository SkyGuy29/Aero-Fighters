#include "Object.h"


Object::Object()
{
}

void Object::update(sf::Vector2u winSize)
{
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Object::nextFrame()
{
	// Increases the image rectangle by its height and loops back when it reaches the end
	currentFrame++;
	if (currentFrame >= frameCount * updatesPFrame)
		currentFrame -= frameCount * updatesPFrame;

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(0, 
		(currentFrame / updatesPFrame) * sprite.getSize().y,
		sprite.getSize().x, sprite.getSize().y));
}

void Object::setRandColor()
{
	sf::Color c;
	c.r = rand() % 256;
	c.g = rand() % 256;
	c.b = rand() % 256;
	sprite.setFillColor(c);
}

sf::Vector2f Object::getPos()
{
	return pos;
}

sf::Vector2f Object::getSize()
{
	return size;
}

void Object::setTexture(sf::Texture* texPtr)
{
	sprite.setTexture(texPtr);
}

void Object::intersect(Object* targetPtr)
{
	if ((abs(pos.x - targetPtr->getPos().x) <= (size.x / 2 + targetPtr->getSize().x / 2))
		&& (abs(pos.y - targetPtr->getPos().y) <= (size.y / 2 + targetPtr->getSize().y / 2)))
	{
		//Whatever they need to do on intersect
	}
}

int Object::getType()
{
	return -1;
	//Player is 0
	//Enemy is 1
	//Collectable is 2
	//Projectile is 3
}

void Object::rotate(float angle)
{
	rot = angle;
	sprite.setRotation(rot);
}

void Object::setRotation(float newAngle)
{
	rot = newAngle;
	sprite.setRotation(rot);
}

void Object::move(sf::Vector2f offset, sf::Vector2u winSize)
{
	pos += offset * vel;
	if (pos.x - size.x / 2.f < 0)
		pos.x = size.x / 2.f;
	if (pos.y - size.y / 2.f < 0)
		pos.y = size.y / 2.f;
	if (pos.x + size.x / 2.f >= winSize.x)
		pos.x = winSize.x - size.x / 2.f;
	if (pos.y + size.y / 2.f >= winSize.y)
		pos.y = winSize.y - size.y / 2.f;
	sprite.setPosition(pos);
}

void Object::move(float offsetX, float offsetY, sf::Vector2u winSize)
{
	move(sf::Vector2f(offsetX, offsetY), winSize);
}

void Object::setPos(sf::Vector2f newPos)
{
	pos = newPos;
	sprite.setPosition(pos);
}

void Object::setPos(float newPosX, float newPosY)
{
	setPos(sf::Vector2f(newPosX, newPosY));
}

void Object::setSize(sf::Vector2f newSize)
{
	size = newSize;
	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Object::setSize(float newSizeX, float newSizeY)
{
	setSize(sf::Vector2f(newSizeX, newSizeY));
}

bool Object::outOfBounds(sf::Vector2u winSize)
{
	return (
		pos.x - size.x / 2.f < 0 || pos.y - size.y / 2.f < 0 || 
		pos.x + size.x / 2.f >= winSize.x || pos.y + size.y / 2.f >= winSize.y);
}

bool Object::shouldDelete()
{
	return del;
}