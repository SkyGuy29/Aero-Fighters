#include "Object.h"


Object::Object()
{
}

void Object::update(sf::Vector2u winSize, std::vector<Object*>*)
{
}

void Object::objectUpdate(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	move(winSize);
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

// for objects that need animations, DON'T FORGET TO SET frameCount
// this is the new animator
void Object::nextFrame()
{
	// Increases the image rectangle by its height and loops back when it reaches the end
	currentFrame++;
	if (currentFrame >= frameCount * 15)
		currentFrame -= frameCount * 15;

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(0, 
		(currentFrame / 15) * sprite.getSize().y,
		sprite.getSize().x, sprite.getSize().y));
}

// just a temporary method, idk why I remade it lol
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

short Object::getID()
{
	return id;
}

// The use of this method is to load a texture in Level or Game once, then cheaply load it again multiple times
void Object::setTexture(sf::Texture* texPtr)
{
	sprite.setTexture(texPtr);
}

bool Object::intersect(Object* targetPtr)
{
	return (abs(pos.x - targetPtr->getPos().x) <= (size.x / 2 + targetPtr->getSize().x / 2))
		&& (abs(pos.y - targetPtr->getPos().y) <= (size.y / 2 + targetPtr->getSize().y / 2));
}

short Object::getType()
{
	return type;
}

short Object::getId()
{
	return id;
}

// I was thinking move would need a boundry check, not setPos.
void Object::move(sf::Vector2u winSize)
{
	pos += vel;
	if (type == PLAYER)
	{
		if (pos.x - size.x / 2.f < 0)
			pos.x = size.x / 2.f;
		if (pos.y - size.y / 2.f < 0)
			pos.y = size.y / 2.f;
		if (pos.x + size.x / 2.f >= winSize.x)
			pos.x = winSize.x - size.x / 2.f;
		if (pos.y + size.y / 2.f >= winSize.y)
			pos.y = winSize.y - size.y / 2.f;
	}
	sprite.setPosition(pos);
}

// setPos was more of a setup thing, and you know exactly where it will be going.
void Object::setPos(sf::Vector2f newPos)
{
	pos = newPos;
	sprite.setPosition(pos);
}

void Object::setPos(float newPosX, float newPosY)
{
	setPos(sf::Vector2f(newPosX, newPosY));
}

// I just wanted to reduce code repitition for setting the sprite origin, so might as well make it useful
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

sf::Vector2f Object::getVel()
{
	return vel;
}

void Object::setVel(sf::Vector2f newVel)
{
	vel = newVel;
}

void Object::setVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}

// returns if any part of an object is outside the viewing area
bool Object::outOfBounds(sf::Vector2u winSize)
{
	return (
		pos.x + size.x / 2.f < 0 || pos.y + size.y / 2.f < 0 || 
		pos.x - size.x / 2.f >= winSize.x || pos.y - size.y / 2.f >= winSize.y);
}

void Object::setDelete()
{
	del = true;
}

bool Object::shouldDelete()
{
	return del;
}