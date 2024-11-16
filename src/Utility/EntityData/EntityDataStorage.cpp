#include "EntityDataStorage.h"

#include <SFML/Graphics/Rect.hpp>

#include "EntityData.hpp"
#include "../EntityID.h"
//std::unordered_map<unsigned int, sf::Sprite*> EntityDataStorage::spriteTable;
std::unordered_map<EntityDataStorage::EntityData::SpriteData::TextureType, sf::Texture*> EntityDataStorage::EntityData::textureMap;


void EntityDataStorage::loadTextures()
{
	std::unordered_map<EntityData::SpriteData::TextureType, sf::Texture*>& textureMap = EntityData::getTextureMap();
	// ^ \/ parellel w/ textureType
	const std::vector<std::string> textureStrings = {
		"res/Misc/players.png", // PLAYER
		"res/Misc/Projectiles.png", // PROJECTILE,
		"res/Misc/Powerups.png", // POWER_UP,
		"res/Misc/money.png", // MONEY,
		"res/Misc/Explosion.png", // EXPLOSION,
		"res/Misc/enemies.png", // ENEMY,
		"res/Misc/Enemy projectiles.png", // ENEMY_PROJECTILE,
		"res/Misc/missles.png", // MISSILE,
		"res/England/House.png", // HOUSE,
		"res/England/Dome.png", // DOME,
		"res/England/Gate.png", // GATE,
		"res/England/Hood.png", // HOOD,
		"res/England/Cone.png", // CONE,
		"res/England/Roofus.png", // ROOFUS
		"res/England/Dome animation.png", // DOME_ANIMATION,
		"res/England/Avro Bomber.png", // AVRO_BOMBER,
	};
	sf::Texture* temp;
	for (unsigned int i = 0; i < textureStrings.size(); i++)
	{
		temp = new sf::Texture(); // expected to unload from the textureMap
		textureMap[(EntityData::SpriteData::TextureType)i] = temp;
		temp->loadFromFile(textureStrings[i]);
	}
}


void EntityDataStorage::unloadTextures()
{
	std::unordered_map<EntityData::SpriteData::TextureType, sf::Texture*>& textureMap = EntityData::getTextureMap();
	for (auto& texture : textureMap)
		delete texture.second;
}

/*
VariableArray<
	EntityDataStorage::ProjectilePrototype,
	/*get Total/0,
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
	*/
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
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,440,32,32
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
	// ENEMY_AIR_COUNT, (null)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,0,0
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_LAND_CHILD_TANK_WEAK_TOP_GREEN,
	EntityData{
			EntityData::SpriteData {
				sf::IntRect {
					0,40,32,32
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
	// ENEMY_LAND_CHILD_TANK_STRONG_TOP_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,80,32,32
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
	// ENEMY_LAND_TANK_BOTTOM_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,32,32
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
	// ENEMY_LAND_CHILD_TANK_WEAK_TOP_YELLOW,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,160,32,32
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
	// ENEMY_LAND_CHILD_TANK_STRONG_TOP_YELLOW,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,200,32,32
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
	// ENEMY_LAND_TANK_BOTTOM_YELLOW,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,120,32,32
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
	// ENEMY_LAND_TURRET_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,840,32,32
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
	// ENEMY_LAND_TURRET_BLUE,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,880,32,32
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
	// ENEMY_LAND_TURRET_GRAY,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,920,32,32
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
	// ENEMY_LAND_LANDMINE,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,240,32,32
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
	// ENEMY_LAND_SPACE_MINE,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,280,32,32
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
	// ENEMY_LAND_DESTROYED_TANK_GREEN,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,480,32,32
			},
			1,
			5,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_LAND_DESTROYED_TANK_YELLOW,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				520,520,32,32
			},
			1,
			5,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_LAND_COUNT, (null)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,0,0
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_WATER_COUNT, (null)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,0,0
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// ENEMY_COUNT, (null)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,0,0
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::ENEMY
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_DOME_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,80,80
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::DOME
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_ROOFUS_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,48,48
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::ROOFUS
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_CONE_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,48,48
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::CONE
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_HOUSE_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,64,48
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::HOUSE
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_GATE_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,32,40
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::GATE
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_HANGAR_ENGLAND,
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,80,96
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::HOOD
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// TILE_ENTITY_COUNT, (null)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,80,96
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::HOOD
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// SPAWNER (null for now)
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,0,80,96
			},
			1,
			1,
			true,
			EntityData::SpriteData::TextureType::HOOD
		},
		Vec2f { 0, 0 },
		0,
		0,
		0b00000000
	},
	// PLAYER TODO: figure out other player animation stuff
	EntityData{
		EntityData::SpriteData {
			sf::IntRect {
				0,16,32,32
			},
			16,
			5,
			true,
			EntityData::SpriteData::TextureType::PLAYER
		},
		Vec2f { 0, 0 },
		3,
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