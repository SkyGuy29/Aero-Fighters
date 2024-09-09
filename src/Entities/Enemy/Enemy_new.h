#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"

// Primarily used by 
class Enemy :
    private Entity, private IHasHealth
{
public:
	Enemy(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned char orientation = 0) :
		Entity(pos, vel, ID, orientation), IHasHealth(ID) {}

	~Enemy();

	void tick(EntityHolder entities) override;
protected:

private:
};