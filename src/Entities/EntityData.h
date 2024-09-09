#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/EntityID.h"
#include "../Utility/Array/StaticArray.h"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
{
public:
	// Must never be constructed
	EntityDataStorage() = delete;

	// Stores a given entities cooldown information for quick access
	struct Cooldown
	{
		// The base cooldown for this entity
		short baseCooldown;
		// The current cooldown timer (Counts down to 0)
		short currentCooldown;

		Cooldown(const short BaseCooldown, short CurrentCooldown) :
			baseCooldown(BaseCooldown), currentCooldown(CurrentCooldown) {}
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

	/**
	 * Returns the baseline data for a given entity.
	 *
	 * @param ID The ID of the entity whose data is being requested
	 * @return A constant reference to an EntityData object
	 */
	static const EntityData& getData(EntityID ID)
	{
		return EntityDataTable[static_cast<unsigned char>(ID)];
	}


private:
	// Entity Data Table
	static const EntityData EntityDataTable[] =
	{
		{
			EntityData {
				{
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
};