#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"
#include "../../Utility/EntityData/EntityPrototype.h"
#include "../Interfaces/ICollidable.h"

// Primarily used by 
class Enemy_new :
	public Entity, protected IHasHealth, public ICollidable
{
public:
	Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned char orientation = 0);
	// dont be null :pray:
	Enemy_new(EntityPrototype* prototype) : Enemy_new(prototype->SPAWN_POS, prototype->SPAWN_VELOCITY, prototype->ID) {};
	~Enemy_new() override;

	void tick() override;
	const sf::IntRect& getBounds() const noexcept override
	{
		return EntityDataStorage::getEntity(Entity::getUUID()).getTextureRect();
	}

	const bool CollidesWith(ICollidable* other) const noexcept override
	{
		return other->getBounds().intersects(getBounds());
	}
protected:
	float* backgroundSpeed = nullptr;
	bool entered = false;

};