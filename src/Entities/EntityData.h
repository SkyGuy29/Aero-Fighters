#pragma once
#include "../Utility/EntityID.h"
#include "SFML/System/Vector2.hpp"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
{
public:
	// Must never be constructed
	EntityDataStorage() = delete;

	// The stored default information for a given entity; very generic.
	struct EntityData
	{
		// This entities base velocity
		const Vec2f velocity;
		// This entities base health
		const unsigned short health;
		// This entities base cooldown information
		const short baseCooldown;

		// Holds data regarding is the entity has children (LSB IE right-most bit)
		// And if it does then the array element holding its children (left-most 7 MSBs)
		const unsigned char CHILD_DATA;

		EntityData(const Vec2f velocity, const unsigned short health, const short baseCooldown, const unsigned char CHILD_DATA) :
			velocity(velocity), health(health), baseCooldown(baseCooldown), CHILD_DATA(CHILD_DATA) {}
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
	static const EntityData EntityDataTable[];

	// Entity Child Table
};