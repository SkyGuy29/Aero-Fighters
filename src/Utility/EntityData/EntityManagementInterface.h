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
#include "../../Entities/Projectile/Projectile_new.h"
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


	static inline void load(Map map);
	static inline void tick(sf::RenderWindow& win, unsigned int currentTick);
	static inline std::vector<Player_new*>& getPlayers() { return players; };
private:
	static inline void loadAttacks();
	static inline void loadEnemies(Map map);
	// DO NOT REMOVE THE INLINE FROM THIS METHOD
	template<typename T> requires std::derived_from<T, Entity> 
	static inline void generalTick(std::vector<T*>& entities, sf::RenderWindow& win);

	template<typename T> requires std::derived_from<T, Entity>
	static inline void processAttack(EntityDataStorage::AttackID ID, T& entity);

	// tick->list of enemies to spawn. dont delete after spawned cause level editor
	static std::unordered_map<unsigned int, std::vector<EntityPrototype*>> spawnMap;
	static std::vector<Player_new*> players; // spawned at start
	static std::vector<Enemy_new*> landEnemies; // spawned at start (spawnMap:0)
	static std::vector<Enemy_new*> airEnemies; // spawnMap
	static std::vector<Enemy_new*> waterEnemies; // spawnMap
	static std::vector<Boss_new*> bossEnemies; // ?
	static std::vector<Projectile_new*> projectiles; // spawned dynamically by enemies
	static std::vector<PermanentSpawner*> permanentSpawners; // spawned at start ??
	static std::vector<TemporarySpawner*> temporarySpawners; // spawned at start ??
	static std::vector<TileEntity*> tileEntities; // spawned at start (spawnMap:0)
	static std::vector<PowerUp*> powerUps; // spawned dynamically by enemies
	static std::vector<std::vector<ProjectilePrototype>> attackData;
};

template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::generalTick(std::vector<T*>& entities, sf::RenderWindow& win)
{
	Entity::EntityObjectAction action;
	Entity::TickData data;

	// For every entity in the vector
	for (unsigned short i = 0; i < entities.size(); i++)
	{
		switch(entities.at(i).getEntityAction())
		{
		case Entity::EntityObjectAction::DELETE:
			delete entities.at(i);
			entities.erase(i); // and you say you like optimization...
			i--;
			action = Entity::EntityObjectAction::DELETE;
			break;

		case Entity::EntityObjectAction::DRAW: // draw the entity's sprite
			win.draw(EntityDataStorage::getEntity(entities.at(i).getUUID()));
			action = Entity::EntityObjectAction::DRAW;
			break;

		case Entity::EntityObjectAction::NOTHING:
			action = Entity::EntityObjectAction::NOTHING;
			break;
		}

		if (action != Entity::EntityObjectAction::DELETE)
		{
			data = entities.at(i).tick();

			if (data.hasAttacked)
			{
				processAttack<T>(data.attack, entities.at(i));
			}
		}
			
	}
}

template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::processAttack(EntityDataStorage::AttackID ID, T& entity)
{
	ReturnData<EntityDataStorage::ProjectilePrototype> attack = EntityDataStorage::getAttack(ID);
	sf::Vector2f position = entity.getPos();

	projectiles.emplace(new Projectile_new())
}