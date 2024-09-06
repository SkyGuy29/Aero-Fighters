#pragma once
#include <unordered_map>
#include "../Utility/EntityID.h"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

namespace EntityData
{
	// Stores a given entities cooldown information for quick access
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

	// The stored default information for a given entity; very generic.
	struct EntityData
	{
		// This entities base velocity
		Vec2f velocity;
		// This entities base health
		unsigned short health;
		// This entities base cooldown information
		Cooldown cooldown;

		EntityData(Vec2f velocity, unsigned short health, Cooldown cooldown) :
			velocity(velocity), health(health), cooldown(cooldown) {}
	};



	// Entity Data Table
	// TODO: Replace with array, static_cast accessor
	// Stores Key value pairs, the Key is the EntityID,
	// the value is the entities data
	const std::unordered_map<EntityID, EntityData> EntityDataTable =
	{
		{
			EntityID::ENEMY_AIR_BABY_COPTER,
			EntityData {
				Vec2f {
					0, // X
					0  // Y
				},
				0, // Health
				Cooldown {
					0, // Base Cooldown
					0  // Current Cooldown
				}
			}
		}, // Add other values
	};
}