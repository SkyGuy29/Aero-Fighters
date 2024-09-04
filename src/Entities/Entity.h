#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"
#include "../EntityData.h"

using Vec2f = sf::Vector2f;

class Entity
{ 
public:
	struct EntityHolder
	{
		// All enemy entities
		std::vector<Entity*> Enemies;

		// All projectile entities
		std::vector<Entity*> Projectiles;

		// All other entities
		std::vector<Entity*> Other;
	};
	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual void tick(EntityHolder entities) = 0;

	// Sets the variable used by entity for the size of the window.
	// Should only ever be called once, giving a variable held
	// before level is instantiated.
	void setWinSize(WindowSize& winSize);

protected:

	Entity(sf::Vector2f pos, sf::Vector2f vel,
		   EntityID ID, unsigned char orientation = 0) :
		pos(pos), ID(ID), orientation(orientation) {}

	// Returns if this entity is currently visible
	inline bool onScreen() noexcept;

	inline bool hasSpawned() noexcept;

	// The position of this entity
	sf::Vector2f pos;
	// The velocity of this entity
	// Derived during object construction
	sf::Vector2f vel = { EntityData::EntityDataTable.at(ID).velocity.x, EntityData::EntityDataTable.at(ID).velocity.y };
	// The attack cooldown of this entity
	// Derived during object construction from the entity data table.
	EntityData::Cooldown cooldown = EntityData::EntityDataTable.at(ID).cooldown;

	// This entities current orientation
	// Only used when drawing - entity specific
	unsigned char orientation;

	// The ID of this entity
	const EntityID ID;
private:
	static WindowSize& winSize;

	// null / null / null / null / null / null / null / hasSpawned
	bool entityFlags = 0b00000000;
};

