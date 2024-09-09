#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility/EntityID.h"
#include "../Utility/Array/StaticArray.h"

// Included by src/Entities/Entity.h

using cstr = const char* const;
using Vec2f = sf::Vector2f;

class SpriteDataStorage
{
public:
	// Class may never be constructed
	SpriteDataStorage() = delete;

	/**
	 * Holds known baseline data used during the drawing entities
	 *
	 * @warning May only be instantiated as a compile-time constant.
	 */
	struct SpriteData
	{
		// The filename where the texture is stored
		constexpr cstr filename;
		// The size of the sprite
		constexpr Vec2f size;
		// The number of animation frames
		constexpr unsigned char animationFrameCount;

		/**
		 * Constructs the SpriteData object using known baseline data.
		 *
		 * @param filename The filename where the texture is stored
		 * @param size The size of the sprite
		 * @param animationFrameCount The number of animation frames
		 */
		constexpr SpriteData(cstr filename, const Vec2f size,
			const unsigned char animationFrameCount) :
			filename(filename), size(size), animationFrameCount(animationFrameCount) {}
	};

	/**
	 * Returns compile-time constant data regarding specific
	 * baseline data for entities.
	 *
	 * @param ID The ID of the entity being requested
	 * @return The SpriteData for the requested entity
	 */
	static const SpriteData& getSpriteData(EntityID ID) const
	{
		return SPRITE_DATA_TABLE.at(static_cast<unsigned char>(ID));
	}

	/**
	 * Stores a texture that is loaded during runtime.
	 *
	 * @param ID The ID of the entity whose texture is being stored
	 * @param texture The texture of the entity being stored
	 */
	static void addTexture(const EntityID ID, const sf::Texture texture)
	{
		textureTable.emplace(ID, texture);
	}

	/**
	 * Used to retrieve a stored texture.
	 *
	 * @param ID The ID of the entity texture being requested
	 * @return The requested texture
	 */
	static const sf::Texture& getTexture(EntityID ID) const
	{
		return textureTable.at(ID);
	}

private:
	// Compile-time constant data for sprite baselines.
	static constexpr StaticArray<SpriteData> SPRITE_DATA_TABLE =
	{
		{"baby_copter_filename", {0,0}, 0}, // Set real filename & Frame count
		{"big_plane_filename", {0,0}, 0}, // Set real filename & Frame count
		{"spinny_plane_filename", {0,0}, 0}, // Set real filename & Frame count
		{"chopper_blades_filename", {0,0}, 0}, // Set real filename & Frame count
	};

	static std::unordered_map<EntityID, sf::Texture> textureTable;
};