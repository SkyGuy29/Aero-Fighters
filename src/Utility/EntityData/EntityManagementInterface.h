#pragma once

#include "EntityDataStorage.h"
#include "Enemy/Enemy_new.h"
#include "Player/Player_new.h"
#include "PowerUp/PowerUp.h"
#include "Spawner/PermanentSpawner/PermanentSpawner.h"
#include "Spawner/TemporarySpawner/TemporarySpawner.h"
#include "TileEntity/TileEntity.h"
#include "Enemy/Boss/Boss_new.h"

class EntityManagementInterface
{
public:
	EntityManagementInterface() = delete;
	~EntityManagementInterface() = delete;


	static inline void tick(Entity* entity);
	static inline void draw(sf::RenderWindow& win);

private:
	// DO NOT REMOVE THE INLINE FROM THIS METHOD
	static inline void generalTick();


	static std::vector<Enemy_new*> landEnemies;
	static std::vector<Enemy_new*> airEnemies;
	static std::vector<Enemy_new*> waterEnemies;
	static std::vector<Boss_new*> bossEnemies;
	static std::vector<Projectile*> projectiles;
	static std::vector<PermanentSpawner*> permanentSpawners;
	static std::vector<TemporarySpawner*> temporarySpawners;
	static std::vector<TileEntity*> tileEntities;
	static std::vector<PowerUp*> powerUps;
};

