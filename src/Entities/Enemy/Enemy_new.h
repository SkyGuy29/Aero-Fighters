#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"

// Primarily used by 
class Enemy_new :
	protected Entity, protected IHasHealth
{
public:
	Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
		backgroundSpeed(backgroundSpeed), Entity(pos, ID, orientation), IHasHealth(ID) {}

	~Enemy_new();

	void tick(EntityHolder& entities) override;
protected:
	int* backgroundSpeed = nullptr;
	bool entered = false;
private:
};