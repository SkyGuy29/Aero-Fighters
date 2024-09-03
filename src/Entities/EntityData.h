#pragma once
#include <unordered_map>
#include "../Utility/EntityID.h"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

namespace EntityData
{

	struct Cooldown
	{
		// The base cooldown for this entity
		constexpr short BaseCooldown;
		// The current cooldown timer
		// (CurrentCooldown != BaseCooldown ? ++CurrentCooldown)
		constexpr short CurrentCooldown;

		constexpr Cooldown(const short BaseCooldown, short CurrentCooldown) :
			BaseCooldown(BaseCooldown), CurrentCooldown(CurrentCooldown) {}
	};

	struct EntityData
	{
		constexpr Vec2f velocity;
		constexpr unsigned short health;
		constexpr Cooldown cooldown;

		constexpr EntityData(Vec2f velocity, unsigned short health, Cooldown cooldown) :
			velocity(velocity), health(health), cooldown(cooldown) {}
	};


	constexpr std::unordered_map<EntityID, EntityData> EntityDataTable =
	{
		{
			EntityID::ENEMY_AIR_BABY_COPTER,
			{{0,0}, 0, {0,0}}
		}, // Add other values
	};
}