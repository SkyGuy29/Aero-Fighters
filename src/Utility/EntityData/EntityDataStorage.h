#pragma once
#include <vector>

#include "../Utility/EntityID.h"
#include "SFML/System/Vector2.hpp"
#include <stdint.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

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

	struct ProjectilePrototype;

	class AttackPrototype;

	// The stored default information for a given entity; very generic.
	struct EntityDataStorage;

	/**
	 * Returns the baseline data for a given entity.
	 *
	 * @param ID The ID of the entity whose data is being requested
	 * @return A constant reference to an EntityData object
	 */
	static const EntityDataStorage& getData(EntityID ID)
	{
		return EntityDataTable[static_cast<uint8_t>(ID)];
	}

private:
	// Entity Data Table
	static EntityDataStorage const EntityDataTable[static_cast<unsigned char>(EntityID::COUNT)];

	// Attack Spawning Table
	//static const VariableArray<Projectile>


	/**
	 * Brain Food
	 *
	 * ref
	 *
	 */

	// Projectile Data Table

	// Entity Child Table
};