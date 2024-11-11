#include "TileEntity.h"

const ICollidable::CollisionType TileEntity::CollidesWith(ICollidable* other) const noexcept
{
	return ICollidable::CollidesWith(other);
}

const sf::IntRect& TileEntity::getBounds() const noexcept
{
	// TODO not return reference to temporary object
	return sf::IntRect(0,0,0,0);
}
