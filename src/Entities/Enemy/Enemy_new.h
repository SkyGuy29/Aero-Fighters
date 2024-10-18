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
	// ANDREW HERE make line work
	Enemy_new(EntityPrototype* prototype) : line(prototype->LINE), Enemy_new(prototype->SPAWN_POS, prototype->SPAWN_VELOCITY, prototype->ID) {};
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
	// the line in the enemies file that the enemy is spawned from (for level editor), provided by prototype only
	unsigned int line;
};