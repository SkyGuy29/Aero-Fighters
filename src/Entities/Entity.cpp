#include "Entity.h"
#include "../Sprites/SpriteType.h"


bool Entity::onScreen()
{
	return !(pos.x + (sprites::spriteDataTable.at(ID).size.x / 2.f) < 0 ||              // Off the left
		     pos.y + (sprites::spriteDataTable.at(ID).size.x / 2.f) < 0 ||              // Off the top
		     pos.x - (sprites::spriteDataTable.at(ID).size.x / 2.f) >= winSize.width || // Off the right
		     pos.y - (sprites::spriteDataTable.at(ID).size.x / 2.f) >= winSize.height); // Off the bottom
}


bool Entity::hasSpawned()
{
	return entityFlags & 0b00000001;
}