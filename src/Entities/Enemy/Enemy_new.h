#pragma once
#include "../Entity.h"
#include "../../Projectile/Projectile_new.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"

// Primarily used by 
class Enemy :
	protected Entity, protected IHasHealth
{
public:
	Enemy(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
		backgroundSpeed(backgroundSpeed), Entity(pos, vel, ID, orientation), IHasHealth(ID) {}

	~Enemy();

	void tick(EntityHolder& entities) override;
protected:
	int* backgroundSpeed = nullptr;
	bool entered = false;
private:
};