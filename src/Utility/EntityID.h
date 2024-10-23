#pragma once

// List of all entity IDs
enum class EntityID : unsigned char
{
	// Entity type, derivative(if applicable), child(if entity is only ever a child), entity name, variant(if applicable)
	ENEMY_AIR_THICK_HELI_GREEN,
	ENEMY_AIR_THICK_HELI_RED,
	ENEMY_AIR_THIN_HELI_GREEN,
	ENEMY_AIR_THIN_HELI_RED,
	ENEMY_AIR_PLANE_1_GREEN,
	ENEMY_AIR_PLANE_1_RED,
	ENEMY_AIR_PLANE_2_BLUE,
	ENEMY_AIR_PLANE_2_GREEN,
	ENEMY_AIR_PLANE_2_RED,
	ENEMY_AIR_CHILD_CHOPPER_BLADES_SMALL,
	ENEMY_AIR_CHILD_CHOPPER_BLADES_BIG,
	ENEMY_AIR_ADVANCED_MEGACOPTOR,
	ENEMY_AIR_BIG_HELICOPTOR,
	ENEMY_AIR_BIG_PLANE_ANGLED,
	ENEMY_AIR_BIG_PLANE_STRAIGHT,
	ENEMY_AIR_PLANE_SPIN_SIDE_GREEN,
	ENEMY_AIR_PLANE_SPIN_SIDE_RED,
	ENEMY_AIR_PLANE_BACKFLIP_GREEN,
	ENEMY_AIR_PLANE_BACKFLIP_RED,
	ENEMY_AIR_COUNT, // DO NOT MOVE; DO NOT USE

	ENEMY_LAND_CHILD_TANK_WEAK_TOP_GREEN,
	ENEMY_LAND_CHILD_TANK_STRONG_TOP_GREEN,
	ENEMY_LAND_TANK_BOTTOM_GREEN,
	ENEMY_LAND_CHILD_TANK_WEAK_TOP_YELLOW,
	ENEMY_LAND_CHILD_TANK_STRONG_TOP_YELLOW,
	ENEMY_LAND_TANK_BOTTOM_YELLOW,
	ENEMY_LAND_TURRET_GREEN,
	ENEMY_LAND_TURRET_BLUE,
	ENEMY_LAND_TURRET_GRAY,
	ENEMY_LAND_LANDMINE,
	ENEMY_LAND_SPACE_MINE,
	ENEMY_LAND_DESTROYED_TANK_GREEN,
	ENEMY_LAND_DESTROYED_TANK_YELLOW,
	ENEMY_LAND_COUNT, // DO NOT MOVE; DO NOT USE

	ENEMY_WATER_COUNT, // DO NOT MOVE; DO NOT USE
	ENEMY_COUNT, // DO NOT MOVE; DO NOT USE

	TILE_DOME_ENGLAND,
	TILE_ROOFUS_ENGLAND,
	TILE_CONE_ENGLAND,
	TILE_HOUSE_ENGLAND,
	TILE_GATE_ENGLAND,
	TILE_HANGAR_ENGLAND,
	TILE_ENTITY_COUNT, // DO NOT MOVE; DO NOT USE

	SPAWNER,
	PLAYER,

	// DO NOT USE
	// MUST BE AT THE END OF THE ENUM
	// Used as a compile-tile constant for entity related tables.
	COUNT
};

struct EntityTypeCounts
{
	// May not construct objects
	EntityTypeCounts() = delete;

	static constexpr unsigned char TOTAL_CHILD_HOLDERS = 1;
};