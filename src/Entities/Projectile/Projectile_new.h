#pragma once
#include "../../Utility/EntityID.h"
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../../Utility/EntityData/ProjectilePrototype.h"


class Projectile_new :
	public Entity, public ICollidable
{
public:
	Projectile_new(const ProjectilePrototype prototype, Entity* owner);

	TickData tick() override;
	virtual void move();


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
	ProjectilePrototype::Owner ownerType;
	Entity* owner;
};