#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"
#include "../../Utility/EntityData/EntityPrototype.h"

// Primarily used by 
class Enemy_new :
	public Entity, protected IHasHealth
{
public:
	Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned int line = 0);
	// dont be null :pray:
	// ANDREW HERE make line work
	Enemy_new(EntityPrototype* prototype) : Enemy_new(prototype->SPAWN_POS, prototype->SPAWN_VELOCITY, prototype->ID, prototype->LINE) {};
	~Enemy_new() override;

	void tick() override;
protected:
	float* backgroundSpeed = nullptr;
	bool entered = false;
	// the line in the enemies file that the enemy is spawned from (for level editor), provided by prototype only
	unsigned int line;
};