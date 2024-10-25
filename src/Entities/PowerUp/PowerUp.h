#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class PowerUp :
	private Entity, public ICollidable
{
public:


    TickData tick() override;


	const sf::IntRect& getBounds() const noexcept override
	{
		return EntityDataStorage::getEntity(Entity::getUUID()).getTextureRect();
	}

	// The overridden collision method for enemies to handle children
	const CollisionType CollidesWith(ICollidable* other) const noexcept override
	{
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		return ret;
	}
private:
};

