#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "EntityData.h"
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"

class Entity
{ 
public:
	struct EntityHolder
	{
		// All enemy entities
		std::vector<Entity*> enemies;

		// All projectile entities
		std::vector<Entity*> projectiles;

		// All other entities
		std::vector<Entity*> other;
	};
	virtual ~Entity() = default;

	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual void tick(EntityHolder& entities) = 0;

	// Sets the variable used by entity for the size of the window.
	// Should only ever be called once, giving a variable held
	// before level is instantiated.
	void setWinSize(WindowSize& winSize);

protected:
	Entity(sf::Vector2f pos, EntityID ID, unsigned char orientation = 0);

	// Returns if this entity is currently visible
	inline bool onScreen() const noexcept;

	inline bool hasSpawned() const noexcept;

	sf::Sprite sprite;

	// The position of this entity
	sf::Vector2f pos;

	// The velocity of this entity
	// Derived during object construction
	sf::Vector2f vel = EntityDataStorage::getData(ID).velocity;

	// The attack cooldown of this entity
	// Derived during object construction from the entity data table.
	unsigned short cooldown = EntityDataStorage::getData(ID).baseCooldown;

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

