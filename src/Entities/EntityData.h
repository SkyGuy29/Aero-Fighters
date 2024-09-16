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

	struct ProjectilePrototype
	{
		const sf::Vector2f SPAWN_OFFSET;
		const sf::Vector2f BASE_VELOCITY;
		const EntityID ID;

		operator Projectile*() const
		{
			//new Projectile()
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
		// need to store sprites...
		// Entities either have a sprite variant set, OR an animation, or only 1 image...
		// Store image section rectangle
		// store is animated
		// store count
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
	static EntityData EntityDataTable[static_cast<unsigned char>(EntityID::COUNT)];

	// Attack Spawning Table
	static const VariableArray<Projectile>


	/**
	 * Brain Food
	 *
	 * ref
	 *
	 */

	// Projectile Data Table

	// Entity Child Table
};