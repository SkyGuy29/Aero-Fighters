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
		pos(pos), ID(ID), orientation(orientation),
		Entity(pos, vel, ID), IHasHealth(ID) {}

	~Enemy();

	void tick(EntityHolder entities) override;

protected:

private:
};