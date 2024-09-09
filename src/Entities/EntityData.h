#pragma once
#include "../Utility/Array/StaticArray.h"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
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

		// Holds data regarding is the entity has children (least significant bit IE right-most)
		// And if it does then the array element holding its children (left-most 7 most significant bits)
		const unsigned char CHILD_DATA;

		EntityData(Vec2f velocity, unsigned short health, Cooldown cooldown, unsigned char CHILD_DATA) :
			velocity(velocity), health(health), cooldown(cooldown), CHILD_DATA(CHILD_DATA) {}
	};



	// Entity Data Table
	// TODO: Replace with array, static_cast accessor
	// Stores Key value pairs, the Key is the EntityID,
	// the value is the entities data
	const StaticArray<
		EntityData,
		1 //static_cast<unsigned char>(EntityID::COUNT)
	> EntityDataTable =
	{
		{
			EntityData {
				Vec2f {
					0, // X
					0  // Y
				},
				0, // Health
				Cooldown {
					0, // Base Cooldown
					0  // Current Cooldown
				},
				0 // CHILD_DATA
			} // Add other values
		}
	};

	// Entity Child Table
}