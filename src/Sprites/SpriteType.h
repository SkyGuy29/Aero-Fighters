#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace sprites
{
	// List of all entity IDs
	enum class EntityID : unsigned char
	{
		ENEMY_AIR_BABY_COPTER          = 0,
		ENEMY_AIR_BIG_PLANE            = 14,
		ENEMY_AIR_SPINNY_PLANE         = 15,
		ENEMY_AIR_CHILD_CHOPPER_BLADES = 19,
	};

	const std::unordered_map<EntityID, const char* const> ID_TO_FILENAME =
	{
		{EntityID::ENEMY_AIR_BABY_COPTER, "baby_copter_filename"},
		{EntityID::ENEMY_AIR_BIG_PLANE, "big_plane_filename"},
		{EntityID::ENEMY_AIR_SPINNY_PLANE, "spinny_plane_filename"},
		{EntityID::ENEMY_AIR_CHILD_CHOPPER_BLADES, "chopper_blades_filename"},
	};

	std::unordered_map<EntityID, sf::Texture> textureTable;
}