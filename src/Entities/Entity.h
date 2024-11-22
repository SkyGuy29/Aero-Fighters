#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility/EntityData/EntityDataStorage.h"
#include "../Utility/WindowSize.h"
#include "../Utility/EntityID.h"
enum class PlayerCountry : uint8_t
{
	AMERICA,
	JAPAN,
	SWEDEN,
	ENGLAND
};
class Player;

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
		std::string attack;
	};

	virtual ~Entity() = default;

	enum class AttackID : unsigned char {
		COUNT
	};

	// Generic definition for any entities tick function
	// Entity holder used for when entities need to check for collision themselves
	virtual TickData tick() = 0;

	static void setViewport(sf::View* vie) { view = vie; }

	static void setBackgroundSpeed(float* speed) { backgroundSpeed = speed; }

	static void setCurrentTick(unsigned int& ct) { currentTick = &ct; }

	//static void setAttackMap(std::unordered_map<std::string, std::vector<ProjectilePrototype>>& map) { attackMap = map; }

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
	EntityObjectAction virtual getEntityAction(bool ignoreDeletion = false) noexcept;

	sf::View* getView() { return view; }

	static float getBackgroundSpeed() { return *backgroundSpeed; }

	unsigned int getUUID() const { return UUID; }

	sf::Sprite* getSprite() const { return sprite; }

	sf::Vector2f getPosition() const { return pos; }


	// public because I am lazy TODO: make getters/setters for this
	static std::unordered_map<unsigned short, std::unordered_map<bool, std::unordered_map<PlayerCountry, std::string>>> playerAttackTree;
	static std::unordered_map<std::string, std::vector<ProjectilePrototype>> attackMap;
protected:
	Entity(sf::Vector2f pos, EntityID ID);

	inline bool hasSpawned() noexcept { return entityFlags & 0b0000001; }

	void nextFrame(const int frameRate = 15);

	// moves the entity by it's velocity multiplied by (currentTick-spawnTick).
	void move() noexcept;

	// The velocity of this entity
	// Derived during object construction
	sf::Vector2f vel;

	// The attack cooldown of this entity
	// Derived during object construction from the entity data table.
	unsigned short baseCooldown;
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
	sf::Vector2f pos;
private:

	// The size of the window
	// THESE ARE ASSUMED TO BE SET, PROGRAM WILL SEGFAULT IF NOT SET
	static unsigned int* currentTick;
	static sf::View* view;
	static float* backgroundSpeed;


	// The next UUID that will be assigned.
	static unsigned int next_uuid;

	// A map of all UUIDs to sprites
	static std::unordered_map<unsigned int, sf::Sprite> spriteMap;

	const unsigned int UUID;

	// Texture specific data members //
	short currentFrame = 0;
	bool animationFinished = false, verticalAnimation = false;

	// null / null / null / null / null / null / null / hasSpawned
	bool entityFlags = 0b00000000;
};