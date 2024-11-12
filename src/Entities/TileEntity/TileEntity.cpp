#include "TileEntity.h"

const ICollidable::CollisionType TileEntity::collidesWith(ICollidable* other) const
{
	return ICollidable::collidesWith(other);
}


const sf::IntRect& TileEntity::getBounds() const
{
	// TODO not return reference to temporary object
	return sf::IntRect(0,0,0,0);
}
