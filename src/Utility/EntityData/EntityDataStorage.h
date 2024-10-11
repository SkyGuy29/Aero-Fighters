#pragma once
#include "../../Utility/EntityID.h"
#include "SFML/System/Vector2.hpp"
#include <stdint.h>
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>

#include "../Array/VariableArray.h"

using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
{
public:

	enum class AttackID : unsigned char
	{
		// MUST REMAIN AT THE END OF THE CLASS
		COUNT
	};

	// Must never be constructed
	EntityDataStorage() = delete;

	struct ProjectilePrototype;

	struct AttackPrototype;

	// The stored default information for a given entity; very generic.
	struct EntityData;

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


	static const ReturnData<ProjectilePrototype> getAttack(AttackID ID)
	{
		return attackData.at(static_cast<unsigned char>(ID));
	}


	static inline void addEntity(unsigned short UUID, sf::Sprite sprite)
	{
		spriteTable.emplace(UUID, sprite);
	}
	static inline void deleteEntity(unsigned short UUID)
	{
		spriteTable.erase(UUID);
	}
	static inline sf::Sprite& getEntity(unsigned short UUID)
	{
		return spriteTable.at(UUID);
	}

private:
	static std::unordered_map<unsigned short, sf::Sprite> spriteTable;
	// Entity Data Table
	static EntityData const EntityDataTable[static_cast<unsigned char>(EntityID::COUNT)];

	// Attack Spawning Table
	static const VariableArray<ProjectilePrototype, /*get Total*/0, static_cast<unsigned char>(AttackID::COUNT)> attackData;


	/**
	 * Brain Food
	 *
	 * ref
	 *
	 */

	// Projectile Data Table

	// Entity Child Table
};