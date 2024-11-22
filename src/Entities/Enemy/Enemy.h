#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"
#include "../../Utility/EntityData/EntityPrototype.h"
#include "../Interfaces/ICollidable.h"
#include <cmath>

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
	sf::IntRect getBounds() const noexcept override
	{
		return sprite->getTextureRect();
	}
	const CollisionType collidesWith(ICollidable* other) const override
	{
		return CollisionType::MISS;
	}

	unsigned int getLine() { return line; }
protected:
	virtual TickData attack();
	Enemy* child = nullptr;
	float* backgroundSpeed = nullptr;
	bool entered = false;
};