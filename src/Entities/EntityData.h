#pragma once
#include <unordered_map>
#include "../Utility/EntityID.h"

using cstr = const char* const;

namespace EntityData
{
	struct Vec2f
	{
		float x, y;

		Vec2f(float x, float y) : x(x), y(y) {}
	};

	struct Cooldown
	{
		// The base cooldown for this entity
		short BaseCooldown;
		// The current cooldown timer
		// (CurrentCooldown != BaseCooldown ? ++CurrentCooldown)
		short CurrentCooldown;

		Cooldown(const short BaseCooldown, short CurrentCooldown) :
			BaseCooldown(BaseCooldown), CurrentCooldown(CurrentCooldown) {}
	};

	struct EntityData
	{
		Vec2f velocity;
		unsigned short health;
		Cooldown cooldown;

		EntityData(Vec2f velocity, unsigned short health, Cooldown cooldown) :
			velocity(velocity), health(health), cooldown(cooldown) {}
	};


	const std::unordered_map<EntityID, EntityData> EntityDataTable =
	{
		{
			EntityID::ENEMY_AIR_BABY_COPTER,
			{{0,0}, 0, {0,0}}
		}, // Add other values
	};
}