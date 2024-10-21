#include "EntityDataStorage.h"

#include <stdexcept>
#include <SFML/Graphics/Rect.hpp>

#include "EntityData.hpp"
#include "../EntityID.h"


struct EntityDataStorage::EntityData
{

	class SpriteData
	{
	public:
		enum class TextureType : unsigned char
		{
			PLAYER,
			PROJECTILE,
			POWER_UP,
			MONEY,
			EXPLOSION,
			ENEMY,
			ENEMY_PROJECTILE,
			MISSILE,

			// England Textures
			HOUSE,
			DOME,
			GATE,
			HOOD,
			CONE,
			ROOFUS, // Why?
			DOME_ANIMATION,
			AVRO_BOMBER
		};

		SpriteData(sf::IntRect texBounds, unsigned char count,
			bool isAnimated, bool isHorizFlippable, bool isVertFlippable, const TextureType texture) :
			imageBounds(texBounds), count(count), flags(isAnimated | (isHorizFlippable << 1) | (isVertFlippable << 2)), texture(texture) {}

		/**
		 * This overload is used by entities that do not have an animation loop,
		 * and are not orientation specific. this is reserved for single-texture
		 * entities, or variant entities where the order does not matter
		 *
		 * @return A random rectangle that is applicable to this entity
		 */
		sf::IntRect getBounds() const noexcept
		{
			sf::IntRect ret = imageBounds;

			if (count > 1)
				ret.left *= rand() % count;

			return ret;
		}

		/**
		 * This overload is used by entities that are either animated,
		 * or orientation specific. Entities are expected to know the next needed
		 * texture, if they fit one of the aforementioned categories.
		 *
		 * @param n The specific texture bounds in the set to return
		 * @return The bounds of either the next animation frame or the orientation.
		 */
		sf::IntRect getBounds(unsigned char n) const
		{
			sf::IntRect ret = imageBounds;
			unsigned char flippedCount = count;

			// if it flips horizontally
			if (flags & 0b00000010)
				flippedCount *= 2;
			// if it flips vertically
			if (flags & 0b00000100)
				flippedCount *= 2;


			if (n <= count)
				ret.left *= rand() % n;
			else throw std::runtime_error("Invalid texture requested!");

			return ret;
		}

		TextureType getTextureType() const noexcept { return texture; }
		bool isEntityAnimated() const noexcept { return flags & 0b00000001; }

	private:
		const sf::IntRect imageBounds;
		const unsigned char count;
		// null | null | null | null | null | flipsVertically | flipsHorizontally | isAnimated
		const unsigned char flags;
		const TextureType texture;
	};

	const SpriteData sprite;
	// This entities base velocity
	const Vec2f velocity;
	// This entities base health
	const unsigned short health;
	// This entities base cooldown information
	const short baseCooldown;

	// Holds data regarding is the entity has children (MSB IE left-most bit)
	// And if it does then the array element holding its children (right-most 7 LSBs)
	const uint8_t CHILD_DATA;


	EntityData(const SpriteData sprite, const Vec2f velocity, const unsigned short health, const short baseCooldown, const uint8_t CHILD_DATA) :
		sprite(sprite), velocity(velocity), health(health), baseCooldown(baseCooldown), CHILD_DATA(CHILD_DATA) {}

private:
	friend SpriteData;
	// Insert texture ptr references here
};

VariableArray<
	EntityDataStorage::ProjectilePrototype,
	/*get Total*/0,
	static_cast<unsigned char>(EntityDataStorage::AttackID::COUNT)
> const EntityDataStorage::attackData =
{
	{
		ProjectilePrototype {

		}
	},
	{
		SpacingElement {
			0, // Start
			0  // End
		}
	}
};

// Initialize the EntityDataTable here
EntityDataStorage::EntityData const EntityDataStorage::EntityDataTable[static_cast<unsigned char>(EntityID::COUNT)] = {
	// EntityID::ENEMY_AIR_BABY_COPTER
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,240,32,32
			},
			1,
			false,
			false,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				32,240,32,32
			},
			16,
			false,
			false,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
};

// Generic entity
/*
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,0,0,0
			},
			1,
			false,
			false,
			false,
			EntityData::SpriteData::TextureType::PROJECTILE
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	}
	*/