#pragma once
#include "../../Utility/EntityID.h"
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../../Utility/EntityData/ProjectilePrototype.h"
#include <cmath>


class Projectile :
	public Entity, public ICollidable
{
public:
	Projectile(const ProjectilePrototype prototype, Entity* owner);

	TickData tick() override;
	virtual void move();


	sf::IntRect getBounds() const noexcept override
	{
		return sprite->getTextureRect();
	}

	// The overridden collision method for enemies to handle children
	const CollisionType collidesWith(ICollidable* other) const noexcept
	{
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other != this && other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		return ret;
	}

	// The overridden collision method for enemies to handle children
	/*
	const CollisionType collidesWith(ICollidable* other) const noexcept override
	{
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		if (child->collidesWith(other) == CollisionType::HIT)
		{
			child->damage();

			// Self collision takes precedence; manager damage the entity, parents damage children.
			if (ret != CollisionType::HIT)
				ret = CollisionType::CHILD;
		}

		return ret;
	}*/
private:
	ProjectilePrototype::Owner ownerType;
	Entity* owner;
};