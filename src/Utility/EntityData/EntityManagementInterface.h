#pragma once

#include <fstream>
#include "EntityDataStorage.h"
#include "../../Entities/Enemy/Enemy_new.h"
#include "../../Entities/Player/Player_new.h"
#include "../../Entities/PowerUp/PowerUp.h"
#include "../../Entities/Spawner/PermanentSpawner/PermanentSpawner.h"
#include "../../Entities/Spawner/TemporarySpawner/TemporarySpawner.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss_new.h"
#include "./EntityPrototype.h"
#include "../Array/VariableArray.h"
#include "./ProjectilePrototype.h"


enum Map
{
	England,
	Israel,
	Japan,
	Meddit,
	Russia,
	States,
	Sweden,
	Space
};


const std::vector<std::string> mapStrings = {
	"England",
	"Israel",
	"Japan",
	"Meddit",
	"Russia",
	"States",
	"Sweden",
	"Space"
};


class EntityManagementInterface
{
public:
	EntityManagementInterface() = delete;
	~EntityManagementInterface() = delete;


	static inline void tick(Entity* entity);
	static inline void draw(sf::RenderWindow& win);
	static inline void loadAttacks();
	static inline void loadEnemies(Map map);
private:
	// DO NOT REMOVE THE INLINE FROM THIS METHOD
	static inline void generalTick(Entity* entity);

	// tick->list of enemies to spawn. dont delete after spawned cause level editor
	static std::unordered_map<unsigned int, std::vector<EntityPrototype*>> spawnMap;
	static std::vector<Enemy_new*> landEnemies; // spawned at start (spawnMap:0)
	static std::vector<Enemy_new*> airEnemies; // spawnMap
	static std::vector<Enemy_new*> waterEnemies; // spawnMap
	static std::vector<Boss_new*> bossEnemies; // ?
	static std::vector<Projectile*> projectiles; // spawned dynamically by enemies
	static std::vector<PermanentSpawner*> permanentSpawners; // spawned at start ??
	static std::vector<TemporarySpawner*> temporarySpawners; // spawned at start ??
	static std::vector<TileEntity*> tileEntities; // spawned at start (spawnMap:0)
	static std::vector<PowerUp*> powerUps; // spawned dynamically by enemies
	static std::vector<std::vector<ProjectilePrototype>> attackData;
};