#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "EntityData.h"
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"
// only use pointer
class Player_new;
class Enemy_new;
class Projectile_new;


class EntityHolder
{
public:
	~EntityHolder()
	{
		while (!enemies.empty())
		{
			delete enemies[enemies.size() - 1];
			enemies.pop_back();
		}

		while (!projectiles.empty())
		{
			delete projectiles[projectiles.size() - 1];
			projectiles.pop_back();
		}

		delete players[0];
		delete players[1];

		while (!other.empty())
		{
			delete other[other.size() - 1];
			other.pop_back();
		}
	}
	friend Entity;

	const std::vector<Entity*>& getAllEntities() { return all; };

	// All enemy entities
	std::vector<Enemy_new*> enemies;

	// All projectile entities
	std::vector<Projectile_new*> projectiles;

	// Players
	Player_new* players[2];

	// All other entities
	std::vector<Entity*> other;
private:
	// contains all entities (basically old objects)
	std::vector<Entity*> all;
};


class Entity
{ 
public:
	virtual ~Entity() = default;

	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual void tick() = 0;

	// Sets the variable used by entity for the size of the window.
	// Should only ever be called once, giving a variable held
	// before level is instantiated.
	void setWinSize(WindowSize& winSize);

	sf::Sprite& getSprite() { return sprite; };
	static EntityHolder& getEntities() { return entities;  };
protected:
	Entity(sf::Vector2f pos, EntityID ID, unsigned char orientation = 0);

	// Returns if this entity is currently visible
	inline bool onScreen() const noexcept;

	inline bool hasSpawned() const noexcept;

	void nextFrame(const int frameRate = 15);

	bool getLevelEdtior() { return levelEditor; }

	// The velocity of this entity
	// Derived during object construction
	sf::Vector2f vel = EntityDataStorage::getData(ID).velocity;

	// The attack cooldown of this entity
	// Derived during object construction from the entity data table.
	unsigned short baseCooldown = EntityDataStorage::getData(ID).baseCooldown;
	// Used at timer when ticking for the cooldown.
	unsigned short curCooldown = 0;

	// This entities current orientation
	// Only used when drawing - entity specific
	unsigned char orientation;

	// The ID of this entity
	const EntityID ID;

	sf::Sprite sprite;
private:
	static WindowSize& winSize;
	static bool& levelEditor;
	static EntityHolder entities;


	// Texture specific data mambers //
	short currentFrame = 0;
	bool animationFinished = false, verticalAnimation = false;

	// null / null / null / null / null / null / null / hasSpawned
	bool entityFlags = 0b00000000;
};