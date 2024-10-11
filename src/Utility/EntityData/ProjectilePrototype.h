#pragma once
#include <SFML/System/Vector2.hpp>
#include "../EntityID.h"

struct EntityDataStorage::ProjectilePrototype
{
	const sf::Vector2f SPAWN_OFFSET;
	const sf::Vector2f BASE_VELOCITY;
	const EntityID ID;
};
