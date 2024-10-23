#include "EntityDataStorage.h"

#include <stdexcept>
#include <SFML/Graphics/Rect.hpp>

#include "EntityData.hpp"
#include "../EntityID.h"

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
	// ENEMY_AIR_THICK_HELI_GREEN,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,240,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_THICK_HELI_RED,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,280,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_THIN_HELI_GREEN,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,320,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_THIN_HELI_RED,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,360,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_1_GREEN,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,400,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_1_RED,
	EntityData {
		EntityData::SpriteData {
			sf::IntRect {
				0,440,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_2_BLUE,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,480,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_2_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,520,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_2_RED,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,560,32,32
			},
			1,
			16,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_CHILD_CHOPPER_BLADES_SMALL,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				688,480,32,32
			},
			3,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_CHILD_CHOPPER_BLADES_BIG,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,0,64,64
			},
			3,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_ADVANCED_MEGACOPTOR,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,64,32,96
			},
			1,
			1,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_BIG_HELICOPTOR,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				688,64,48,72
			},
			1,
			1,
			false,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_BIG_PLANE_ANGLED,
	EntityData{
			EntityData::SpriteData {
				sf::IntRect {
					600,64,80,88
				},
				1,
				1,
				false,
				EntityData::SpriteData::TextureType::ENEMY
			},
			Vec2f { 0, 0 },
			0,
			0,
			0b00000000
	},
	// ENEMY_AIR_BIG_PLANE_STRAIGHT,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				600,160,80,80
			},
			2,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_SPIN_SIDE_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,320,32,32
			},
			8,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_SPIN_SIDE_RED,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,360,32,32
			},
			8,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_BACKFLIP_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,400,32,32
			},
			6,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_AIR_PLANE_BACKFLIP_RED,
	// ENEMY_AIR_COUNT,
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