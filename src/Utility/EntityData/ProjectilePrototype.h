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
	// 0/0/0/0/0/0/0/set velocity on start to go to nearest player
	uint8_t FLAGS;
	Owner OWNER;
};