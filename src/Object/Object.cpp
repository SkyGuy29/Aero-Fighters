#include "Object.h"


Object::Object()
{
}


/// <summary>
/// Calls Object::move(winSize) (??? what is the point?)
/// 
/// @@TODO@@
/// Base class version is never called - Declare pure virtual. - Ricky
/// 
/// 
/// </summary>
/// <param name="winSize"></param>
/// <param name="objects"></param>
void Object::objectUpdate(const sf::Vector2f winSize, std::vector<Object*>* objects)
{
	move(winSize);
}


/// <summary>
/// Draws the object to the screen. Implemeneted from sf::Drawable.
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void Object::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(sprite, states);
}

// @@TODO@@
// Move to seperate sprite container class - Unweave the inheritance web - Ricky
//So that the sprite num actually gets updated
void Object::setSpriteNum(const short num)
{
	spriteNum = num;
}


// @@TODO@@
// Move to seperate sprite container class - Unweave the inheritance web - Ricky
//For setting the orientaion of rotating sprites
void Object::setOrientation(const short angle)
{
	orientation = angle;
}


/// <summary>
/// This animator allows for different frame changes.
/// 
/// @@TODO@@
/// Move to seperate sprite container class - Unweave the inheritance web - Ricky
/// </summary>
/// <param name="frameRate"></param>
void Object::nextFrame(const int frameRate = 15)
{
	// Increases the image rectangle by its height and loops back when 
	//it reaches the end
	currentFrame++;
	if (currentFrame >= frameCount * frameRate)
	{
		currentFrame -= frameCount * frameRate;
		anDone = true;
	}

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(
		texOffset.x + (currentFrame / frameRate) * texSize.x 
		* !verticalAnimation,
		texOffset.y + (currentFrame / frameRate) * texSize.y 
		* verticalAnimation,
		texSize.x, texSize.y));
}


/// <summary>
/// 
/// The purpose of this method is to load a texture in Level or Game once,
/// then cheaply load it again multiple times
/// 
/// </summary>
/// <param name="texPtr"></param>
/// <param name="size"></param>
/// <param name="offset"></param>
/// <param name="frameCount"></param>
/// <param name="vertAnimation"></param>
void Object::setTexture(sf::Texture* texPtr, const sf::Vector2i size,
	const sf::Vector2i offset, const int frameCount, const bool vertAnimation)
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


bool Object::intersect(Object* targetPtr) const
{
	if (size.x == 0 || size.y == 0 || targetPtr->getSize().x == 0 
	|| targetPtr->getSize().y == 0)
		return false;
	return (abs(pos.x - targetPtr->getPos().x) <= (size.x / 2 
		+ targetPtr->getSize().x / 2))
		&& (abs(pos.y - targetPtr->getPos().y) <= (size.y / 2 
		+ targetPtr->getSize().y / 2));
}


// I was thinking move would need a boundry check, not setPos.
// @@TODO@@
// Move to seperate sprite container class - Unweave the inheritance web - Ricky
// Base method is never used -- Make pure virtual or delete - Ricky
void Object::move(sf::Vector2f winSize)
{
	pos += vel;
	sprite.setPosition(pos);
}


// setPos was more of a setup thing, and you know exactly where it will 
// be going.
void Object::setPos(sf::Vector2f newPos)
{
	pos = newPos;
	sprite.setPosition(pos);
}


// @@TODO@@
// Cut overloaded function - Wraps a function call that is easier to read without the overload or does the exact same thing as a smaller variant - Ricky
void Object::setPos(float newPosX, float newPosY)
{
	setPos(sf::Vector2f(newPosX, newPosY));
}


// I just wanted to reduce code repitition for setting the sprite origin, 
// so might as well make it useful
void Object::setSize(sf::Vector2f newSize)
{
	size = newSize;
}


// @@TODO@@
// Cut overloaded function - Wraps a function call that is easier to read without the overload or does the exact same thing as a smaller variant - Ricky
void Object::setSize(float newSizeX, float newSizeY)
{
	setSize(sf::Vector2f(newSizeX, newSizeY));
}


void Object::setVel(sf::Vector2f newVel)
{
	vel = newVel;
}


// @@TODO@@
// Cut overloaded function - Wraps a function call that is easier to read without the overload or does the exact same thing as a smaller variant - Ricky
void Object::setVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}


/// <summary>
/// Returns if any part of an object is outside the viewing area.
/// </summary>
/// <param name="winSize"></param>
/// <returns></returns>
bool Object::outOfBounds(sf::Vector2f winSize) const
{
	return pos.x + size.x / 2.f < 0 || pos.y + size.y / 2.f < 0 || 
		pos.x - size.x / 2.f >= winSize.x || pos.y - size.y / 2.f 
		>= winSize.y;
}