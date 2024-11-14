#include "TileEntity.h"

TileEntity::TileEntity(EntityPrototype* prototype)
	: Entity(prototype->SPAWN_POS, prototype->ID)
{

}

Entity::TickData TileEntity::tick()
{
	return TickData();
}


const sf::IntRect& TileEntity::getBounds() const
{
	// TODO not return reference to temporary object
	return sf::IntRect(0,0,0,0);
}
