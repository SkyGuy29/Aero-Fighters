#include "Object.h"


Object::Object()
{
}

//
void Object::update(sf::Vector2u winSize, std::vector<Object*>*, bool time)
{
}

void Object::objectUpdate(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	move(winSize);
}

//draws the object to the screen
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

//This is to get the specific sprite for enemies or projectiles
short Object::getSpriteNum()
{
	return spriteNum;
}

//So that the sprite num actually gets updated
void Object::setSpriteNum(short num)
{
	spriteNum = num;
}

//For setting the orientaion of rotating sprites
void Object::setOrientation(short angle)
{
	orientation = angle;
}

//For getting the orientaion of rotating sprites
short Object::getOrientation()
{
	return orientation;
}

//This animator allows for different frame changes.
void Object::nextFrame(int frameRate = 15)
{
	// Increases the image rectangle by its height and loops back when it reaches the end
	currentFrame++;
	if (currentFrame >= frameCount * frameRate)
	{
		currentFrame -= frameCount * frameRate;
		anDone = true;
	}

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(
		texOffset.x + (currentFrame / frameRate) * texSize.x * !verticalAnimation,
		texOffset.y + (currentFrame / frameRate) * texSize.y * verticalAnimation,
		texSize.x, texSize.y));
}

// The use of this method is to load a texture in Level or Game once, then cheaply load it again multiple times
void Object::setTexture(sf::Texture* texPtr, sf::Vector2i size, sf::Vector2i offset, int frameCount, bool vertAnimation)
{
	texInit = true;
	sprite.setTexture(texPtr);
	texOffset = offset;
	texSize = size;
	this->frameCount = frameCount;
	verticalAnimation = vertAnimation;
	sprite.setSize(sf::Vector2f(size));
	sprite.setOrigin(sf::Vector2f(size) / 2.f);
	nextFrame(2);
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

bool Object::isTexInit()
{
	return texInit;
}

bool Object::intersect(Object* targetPtr)
{
	if (size.x == 0 || size.y == 0 || targetPtr->getSize().x == 0 
	|| targetPtr->getSize().y == 0)
		return false;
	return (abs(pos.x - targetPtr->getPos().x) <= (size.x / 2 + targetPtr->getSize().x / 2))
		&& (abs(pos.y - targetPtr->getPos().y) <= (size.y / 2 + targetPtr->getSize().y / 2));
}

short Object::getType()
{
	return type;
}

// I was thinking move would need a boundry check, not setPos.
void Object::move(sf::Vector2u winSize)
{
	pos += vel;
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