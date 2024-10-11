#pragma once

#include "EntityDataStorage.h"
#include "../../Entities/Enemy/Enemy_new.h"
#include "../../Entities/Player/Player_new.h"
#include "../../Entities/PowerUp/PowerUp.h"h"
#include "../../Entities/Projectile/Projectile_new.h"
#include "../../Entities/Spawner/PermanentSpawner/PermanentSpawner.h"
#include "../../Entities/Spawner/TemporarySpawner/TemporarySpawner.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss_new.h"

class EntityManagementInterface
{
public:
	EntityManagementInterface() = delete;
	~EntityManagementInterface() = delete;


	static inline void tick(sf::RenderWindow& win);\

private:
	// DO NOT REMOVE THE INLINE FROM THIS METHOD
	template<typename T> requires std::derived_from<T, Entity> 
	static inline void generalTick(std::vector<T*>& entities, sf::RenderWindow& win);

	template<typename T> requires std::derived_from<T, Entity>
	static inline void processAttack(EntityDataStorage::AttackID ID, T& entity);


	static std::vector<Enemy_new*> landEnemies;
	static std::vector<Enemy_new*> airEnemies;
	static std::vector<Enemy_new*> waterEnemies;
	static std::vector<Boss_new*> bossEnemies;
	static std::vector<Projectile_new*> projectiles;
	static std::vector<PermanentSpawner*> permanentSpawners;
	static std::vector<TemporarySpawner*> temporarySpawners;
	static std::vector<TileEntity*> tileEntities;
	static std::vector<PowerUp*> powerUps;
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
			entities.erase(i);
			i--;
			action = Entity::EntityObjectAction::DELETE;
			break;

		case Entity::EntityObjectAction::DRAW:
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

