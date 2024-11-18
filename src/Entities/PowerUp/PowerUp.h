#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"


// TODO
class PowerUp final :
	public Entity, public ICollidable
{
public:
	PowerUp(sf::Vector2f spawnPos, EntityID id) :	Entity(spawnPos, id) {};
	~PowerUp() override = default;
    TickData tick() override;


	const sf::IntRect& getBounds() const noexcept override
	{
		return sprite->getTextureRect();
	}

	// The overridden collision method for enemies to handle children
	const CollisionType collidesWith(ICollidable* other) const noexcept override
	{
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		return ret;
	}
private:
};

