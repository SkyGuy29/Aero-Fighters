#pragma once
#include <SFML/Graphics.hpp>
#include "../EntityID.h"


struct EntityPrototype
{
public:
	EntityPrototype(sf::Vector2f spawnPos, sf::Vector2f spawnVelocity, EntityID id, unsigned int tickOffset)
		: SPAWN_POS(spawnPos), SPAWN_VELOCITY(spawnVelocity), ID(id), TICK_OFFSET(tickOffset) {}

	const sf::Vector2f SPAWN_POS, SPAWN_VELOCITY;
	const EntityID ID;
	const unsigned int TICK_OFFSET;
};