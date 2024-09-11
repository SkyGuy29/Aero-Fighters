#include "Entity.h"
#include "../Sprites/SpriteType.h"


Entity::Entity(sf::Vector2f pos,
	EntityID ID, unsigned char orientation) : ID(ID), orientation(orientation)
{
	this->sprite.setPosition(pos);
}


bool Entity::onScreen() const noexcept
{
	return !(pos.x + SpriteDataStorage::getSpriteData(ID).size.x / 2.f < 0 ||              // Off the left
		     pos.y + SpriteDataStorage::getSpriteData(ID).size.y / 2.f < 0 ||              // Off the top
		     pos.x - SpriteDataStorage::getSpriteData(ID).size.x / 2.f >= winSize.width || // Off the right
		     pos.y - SpriteDataStorage::getSpriteData(ID).size.y / 2.f >= winSize.height); // Off the bottom
}


bool Entity::hasSpawned() const noexcept
{
	return entityFlags & 0b00000001;
}


/// <summary>
/// This animator allows for different frame changes.
/// </summary>
/// <param name="frameRate"></param>
void Entity::nextFrame(const int frameRate = 15)
{
	// Increases the image rectangle by its height and loops back when 
	//it reaches the end
	currentFrame++;
	short frameCount = SpriteDataStorage::getSpriteData(ID).animationFrameCount;

	if (currentFrame >= frameCount * frameRate)
	{
		currentFrame -= frameCount * frameRate;
		animationFinished = true;
	}
	sf::Vector2f texSize = SpriteDataStorage::getSpriteData(ID).size;
	sf::Vector2f texOffset = SpriteDataStorage::getSpriteData(ID).textureOffset;

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(
		texOffset.x + (currentFrame / frameRate) * texSize.x
		* !verticalAnimation,
		texOffset.y + (currentFrame / frameRate) * texSize.y
		* verticalAnimation,
		texSize.x, texSize.y));
}