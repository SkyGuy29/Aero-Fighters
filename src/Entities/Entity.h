#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"
#include "EntityData.h"
#define PI 3.14159

using Vec2f = sf::Vector2f;

class Entity
{ 
public:
	virtual ~Entity() = 0;

	struct EntityHolder
	{
		// All enemy entities
		std::vector<Entity*> enemies;

		// All projectile entities
		std::vector<Entity*> projectiles;

		Entity* players[2];

		// All other entities
		std::vector<Entity*> other;
	};
	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual void tick(EntityHolder& entities) = 0;

	// Sets the variable used by entity for the size of the window.
	// Should only ever be called once, giving a variable held
	// before level is instantiated.
	void setWinSize(WindowSize& winSize);

	sf::Sprite sprite;
protected:
	Entity(sf::Vector2f pos,
		EntityID ID, unsigned char orientation = 0);

	// Returns if this entity is currently visible
	inline bool onScreen() noexcept;

	inline bool hasSpawned() noexcept;
	// The ID of this entity
	const EntityID ID;

	sf::Vector2f vel = EntityDataStorage::getData(ID).velocity;
	// The attack cooldown of this entity
	// Derived during object construction from the entity data table.
	EntityDataStorage::Cooldown cooldown = EntityDataStorage::getData(ID).cooldown;

	// This entities current orientation
	// Only used when drawing - entity specific
	unsigned char orientation;

	
private:
	static WindowSize& winSize;

	// null / null / null / null / null / null / null / hasSpawned
	bool entityFlags = 0b00000000;
};

