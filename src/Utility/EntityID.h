#pragma once

// List of all entity IDs
enum class EntityID : unsigned char
{
	// Entity type, derivative(if applicable), child(if entity is only ever a child), entity name, variant(if applicable)
	ENEMY_AIR_BABY_COPTER = 0,
	ENEMY_AIR_BIG_PLANE,
	ENEMY_AIR_SPINNY_PLANE,
	ENEMY_AIR_CHILD_CHOPPER_BLADES,

	ENEMY_LAND_TANK_WEAK,
	ENEMY_LAND_TANK_STRONG,

	TILE_ROOFUS_ENGLAND,
	TILE_CONE_ENGLAND,
	TILE_HOUSE_ENGLAND,
	TILE_GATE_ENGLAND,
	TILE_HANGAR_ENGLAND
};