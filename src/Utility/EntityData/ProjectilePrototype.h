#pragma once
#include <SFML/System/Vector2.hpp>
#include "./EntityPrototype.h"

struct ProjectilePrototype : EntityPrototype
{
	enum class Owner
	{
		Enemy,
		Player1,
		Player2
	};

	ProjectilePrototype(sf::Vector2f spawnPos, sf::Vector2f spawnVelocity, EntityID id, unsigned int tickOffset, uint8_t flags/*, Owner owner*/)
		: EntityPrototype(spawnPos, spawnVelocity, id, tickOffset, 0), FLAGS(flags)/*, OWNER(owner)*/ {}
	
	// 0/0/0/0/0/0/0/set velocity on start to go to nearest player
	const uint8_t FLAGS;
	//const Owner OWNER;
};