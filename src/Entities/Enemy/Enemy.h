#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"
#include "../../Utility/EntityData/EntityPrototype.h"
#include "../Interfaces/ICollidable.h"

// Primarily used by 
class Enemy :
	public Entity, public IHasHealth, public ICollidable
{
public:
	Enemy(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned int line = 0);
	// dont be null :pray:
	// ANDREW HERE make line work
	Enemy(EntityPrototype* prototype) : Enemy(prototype->SPAWN_POS, prototype->SPAWN_VELOCITY, prototype->ID, prototype->LINE) {}
	~Enemy() override;

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

		if (child->CollidesWith(other) == CollisionType::HIT)
		{
			child->damage();

			// Self collision takes precedence; manager damage the entity, parents damage children.
			if (ret != CollisionType::HIT)
				ret = CollisionType::CHILD;
		}

		return ret;
	}

	unsigned int getLine() { return line; }
protected:
	virtual TickData attack();
	Enemy* child = nullptr;
	float* backgroundSpeed = nullptr;
	bool entered = false;
};