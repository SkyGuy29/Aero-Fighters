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