#pragma once

// List of all entity IDs
enum class EntityID : unsigned char
{
	// Entity type, derivative(if applicable), child(if entity is only ever a child), entity name, variant(if applicable)
	ENEMY_AIR_BABY_COPTER = 0,
	ENEMY_AIR_BIG_PLANE = 1,
	ENEMY_AIR_SPINNY_PLANE = 2,
	ENEMY_AIR_CHILD_CHOPPER_BLADES = 3,
};