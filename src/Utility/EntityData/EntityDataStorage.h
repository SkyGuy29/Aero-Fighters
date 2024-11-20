#pragma once
#include "../../Utility/EntityID.h"
#include "SFML/System/Vector2.hpp"
#include <stdint.h>
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Utility/EntityData/ProjectilePrototype.h"
#include "../Array/VariableArray.h"


using cstr = const char* const;
using Vec2f = sf::Vector2f;

class EntityDataStorage
{
public:
	// Must never be constructed
	EntityDataStorage() = delete;

	struct ChildTemplete
	{
		EntityID ID;
		sf::Vector2i parentOffset;
	};

	// The stored default information for a given entity; very generic.
	struct EntityData
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
				ROOFUS,
				DOME_ANIMATION,
				AVRO_BOMBER,
			};

			SpriteData(sf::IntRect texBounds, unsigned char count, unsigned char rotations,
				bool isHorizontal, const TextureType texture) :
				imageBounds(texBounds), count(count), rotations(rotations), flags(isHorizontal), texture(texture) {}

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
			unsigned char getCount() const noexcept { return count; }
			sf::Texture* getTexture() const noexcept { return textureMap.at(texture); }
			unsigned char getRotations() const noexcept { return rotations; }

			TextureType getTextureType() const noexcept { return texture; }

			bool isEntityAnimated() const noexcept { return count > 1; }
			bool isEntityRotatable() const noexcept { return rotations > 1; }
			bool isEntityAnimatedHorizontally() const noexcept { return flags & 1; }
		private:
			const sf::IntRect imageBounds;
			const unsigned char count, rotations;
			// null | null | null | null | null | null | null | isAnimatedHorizontally?
			const unsigned char flags;
			const TextureType texture;
		};
		bool hasChildren() const noexcept
		{
			return CHILD_DATA << 31 != 0;
		}

		const SpriteData spriteData;
		// This entities base velocity
		const Vec2f velocity;
		// This entities base health
		const unsigned short health;
		// This entities base cooldown information
		const short baseCooldown;

		// Holds data regarding is the entity has children (MSB IE left-most bit)
		// And if it does then the array element holding its children (right-most 7 LSBs)
		const uint8_t CHILD_DATA;

		// could be a vector instead of a map (unsure now)
		static std::unordered_map<SpriteData::TextureType, sf::Texture*>& getTextureMap() { return textureMap; }

		EntityData(const SpriteData sprite, const Vec2f velocity, const unsigned short health, const short baseCooldown, const uint8_t CHILD_DATA) :
			spriteData(sprite), velocity(velocity), health(health), baseCooldown(baseCooldown), CHILD_DATA(CHILD_DATA) {}

		EntityData() : spriteData(SpriteData(sf::IntRect(NULL, NULL, NULL, NULL), NULL, NULL, NULL, (SpriteData::TextureType)NULL)),
			velocity(sf::Vector2f(NULL, NULL)), health(NULL), baseCooldown(NULL), CHILD_DATA(NULL)
		{
			//throw std::exception("Failure loading entity data.");
		}
	private:
		friend SpriteData;
		// Insert texture ptr references here
		static std::unordered_map<SpriteData::TextureType, sf::Texture*> textureMap;
	};

	// loads the textures for TextureType
	static void loadTextures();
	static void unloadTextures();

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

	/*static inline void addEntity(unsigned int UUID, sf::Sprite sprite)
	{
		spriteTable.emplace(UUID, &sprite);
	}


	static inline void deleteEntity(unsigned int UUID)
	{
		spriteTable.erase(UUID);
	}


	static inline sf::Sprite* getEntity(unsigned int UUID)
	{
		if(!spriteTable.contains(UUID))
			return nullptr; // TODO
		return spriteTable.at(UUID);
	}*/

private:
	//static std::unordered_map<unsigned int, sf::Sprite*> spriteTable; // bro why is there 2
	// Entity Data Table
	static EntityData const EntityDataTable[static_cast<unsigned char>(EntityID::COUNT)];

	/**
	 * Brain Food
	 *
	 * ref
	 *
	 */

	// Projectile Data Table

	// Entity Child Table
};