#pragma once
#include <vector>

#include "../Utility/EntityID.h"
#include "SFML/System/Vector2.hpp"
#include <stdint.h>

#include "../Utility/Array/VariableArray.h"

class Projectile;
class Entity;
using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
{
public:
	// Must never be constructed
	EntityDataStorage() = delete;

	struct ProjectilePrototype
	{
		const sf::Vector2f SPAWN_OFFSET;
		const sf::Vector2f BASE_VELOCITY;
		const EntityID ID;

		operator Projectile*() const
		{
			new Projectile()
		}
	};

	class AttackPrototype
	{
	public:
		AttackPrototype(const uint8_t SPAWN_INDEX) : SPAWN_INDEX(SPAWN_INDEX) {}


		void spawn(std::vector<Entity*>& projectiles)
		{
			
		}

	private:
		const uint8_t SPAWN_INDEX;
	};

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
		const uint8_t CHILD_DATA;

		EntityData(const Vec2f velocity, const unsigned short health, const short baseCooldown, const uint8_t CHILD_DATA) :
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
		return EntityDataTable[static_cast<uint8_t>(ID)];
	}

private:
	// Entity Data Table
	static const EntityData EntityDataTable[];

	// Attack Spawning Table
	static const VariableArray<Projectile>


	// Projectile Data Table

	// Entity Child Table
};