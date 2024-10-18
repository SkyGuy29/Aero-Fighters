#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility/EntityData/EntityDataStorage.h"
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"


class Entity
{ 
public:
	// Base may not be constructed unless by its derivatives
	Entity() = delete;

	// Helper enum for return action
	enum class EntityObjectAction : unsigned char
	{
		NOTHING = 0,
		DRAW,
		DELETE
	};

	struct TickData
	{
		bool hasAttacked;
		EntityDataStorage::AttackID attack;
	};

	virtual ~Entity() = default;

	enum class AttackID : unsigned char {
		COUNT
	};

	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual void tick() = 0;

	// Sets the variable used by entity for the size of the window.
	// Should only ever be called once, giving a variable held
	// before level is instantiated.
	static void setWinSize(WindowSize& winSize);

	static void setBackgroundSpeed(float& speed) { backgroundSpeed = speed; }

	static void setCurrentTick(unsigned int& ct) { currentTick = ct; }
	
	void setPosition(sf::Vector2f pos);

	/**
	 * Utility method that returns one of three states defining what action must
	 * be performed next on the object.
	 *
	 *
	 * @return What action should be performed on the object.
	 * @retval EntityObjectAction::NOTHING The entity has not been 'spawned',
	 *		   you don't have to do anything.
	 *
	 * @retval EntityObjectAction::DRAW The entity has been spawned and has not
	 *		   left the screen, just draw it.
	 *
	 * @retval EntityObjectAction::DELETE The entity has been 'spawned', however
	 *		   it has just left the screen and thus should be deleted.
	 */
	EntityObjectAction getEntityAction() noexcept;

	unsigned int getUUID() const { return UUID; }

	sf::Sprite* getSprite() { return sprite; }

	sf::Vector2f getPosition() const { return pos; }

protected:
	Entity(sf::Vector2f pos, EntityID ID);

	inline bool hasSpawned() noexcept { return entityFlags & 0b0000001; }

	void nextFrame(const int frameRate = 15);

	// moves the entity by it's velocity multiplied by (currentTick-spawnTick).
	void move() noexcept;

	static float& backgroundSpeed;

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

	sf::Sprite* sprite = nullptr;

	// the line of the file the entity is loaded from. (only tile entities, air, water)
	unsigned int line;

	unsigned int spawnTick;
private:

	// The size of the window
	static WindowSize& winSize;

	// The next UUID that will be assigned.
	static unsigned int next_uuid;

	static unsigned int& currentTick;

	// A map of all UUIDs to sprites
	static std::unordered_map<unsigned int, sf::Sprite> spriteMap;

	const unsigned int UUID;
	sf::Vector2f pos;

	// Texture specific data members //
	short currentFrame = 0;
	bool animationFinished = false, verticalAnimation = false;

	// null / null / null / null / null / null / null / hasSpawned
	bool entityFlags = 0b00000000;
};