#pragma once
#include <SFML/Graphics.hpp>
#include "../EntityID.h"


struct EntityPrototype
{
public:
	sf::Vector2f SPAWN_POS, SPAWN_VELOCITY;
	EntityID ID;
	unsigned int SPAWN_TICK;
};