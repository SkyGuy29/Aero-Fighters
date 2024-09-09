#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility/EntityID.h"

// Included by src/Entities/Entity.h

using cstr = const char* const;
using Vec2f = sf::Vector2f;

namespace sprites
{
	struct SpriteData
	{
		const cstr filename;
		const Vec2f size;
		const unsigned char animationFrameCount;
		unsigned char currentFrame = 0;

		const SpriteData(cstr filename, const Vec2f size,
			const unsigned char animationFrameCount) :
			filename(filename), size(size), animationFrameCount(animationFrameCount) {}
	};

	const std::unordered_map<EntityID, SpriteData> spriteDataTable =
	{
		{EntityID::ENEMY_AIR_BABY_COPTER, {"baby_copter_filename", {0,0}, 0}}, // Set real filename & Frame count
		{EntityID::ENEMY_AIR_BIG_PLANE, {"big_plane_filename", {0,0}, 0}}, // Set real filename & Frame count
		{EntityID::ENEMY_AIR_SPINNY_PLANE, {"spinny_plane_filename", {0,0}, 0}}, // Set real filename & Frame count
		{EntityID::ENEMY_AIR_CHILD_CHOPPER_BLADES, {"chopper_blades_filename", {0,0}, 0}}, // Set real filename & Frame count
	};

	std::unordered_map<EntityID, sf::Texture> textureTable;
}