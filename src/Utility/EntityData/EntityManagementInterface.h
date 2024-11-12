#pragma once

#include <iostream>
#include <fstream>
#include "EntityDataStorage.h"
#include "../../Entities/Enemy/Enemy.h"
#include "../../Entities/Player/Player.h"
#include "../../Entities/PowerUp/PowerUp.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss.h"
#include "../../Entities/Projectile/Projectile.h"
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
	static void updateLevelEditor();
	static inline std::vector<Player*>& getPlayers() { return players; };
	
	// frees memory
	static inline void unload();


	static inline void resetPlayers()
	{
		for (auto player : players)
		{
			player->setHealth(3);
		}
	}

private:
	static inline void loadAttacks();
	static inline void loadEnemies(Map map);

	template<typename T> requires std::derived_from<T, Entity> 
	static void generalTick(std::vector<T*>& entities, sf::RenderWindow& win);

	template<typename T> requires std::derived_from<T, Entity>
	static void processAttack(EntityDataStorage::AttackID ID, T& entity);

	template<typename T> requires std::derived_from<T, Entity>
	static void generalLevelEditorUpdate(std::vector<T*> entities);

	template <typename T, typename V> requires std::derived_from<T, ICollidable>&& std::derived_from<V, ICollidable>
	static bool collide(std::vector<V*>& entities, T* entity);

	static void deleteVector(std::vector<void*>& a);

	// helper function for splitting a string of doubles delimited by spaces
	static std::vector<float> split_(std::string s)
	{
		std::vector<float> ret;
		std::string temp;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == ' ')
				ret.push_back(strtof(temp.c_str(), nullptr));
			else
				temp += s[i];
		}

		return ret;
	}

	// tick->list of enemies to spawn. dont delete after spawned cause level editor
	static std::unordered_map<unsigned int, std::vector<EntityPrototype*>> spawnMap;
	static std::vector<Player*> players; // spawned at start
	static std::vector<Enemy*> landEnemies; // spawned at start (spawnMap:0)
	static std::vector<Projectile*> projectiles; // spawned dynamically by enemies
	static std::vector<Enemy*> airEnemies; // spawnMap
	static std::vector<Enemy*> waterEnemies; // spawnMap
	static std::vector<Boss*> bossEnemies; // ?
	static std::vector<TileEntity*> tileEntities; // spawned at start (spawnMap:0)
	static std::vector<PowerUp*> powerUps; // spawned dynamically by enemies
	static std::unordered_map<std::string, std::vector<ProjectilePrototype>> attackData;

	static unsigned int lastTick;
};

template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::generalTick(std::vector<T*>& entities, sf::RenderWindow& win)
{
	Entity::EntityObjectAction action;
	Entity::TickData data;

	// For every entity in the vector
	for (unsigned short i = 0; i < entities.size(); i++)
	{
		switch(entities.at(i)->getEntityAction())
		{
		case Entity::EntityObjectAction::DELETE:
			delete entities.at(i);
			entities.erase(entities.begin()+i);
			i--;
			action = Entity::EntityObjectAction::DELETE;
			break;

		case Entity::EntityObjectAction::DRAW: // draw the entity's sprite
			win.draw(EntityDataStorage::getEntity(entities.at(i)->getUUID()));
			action = Entity::EntityObjectAction::DRAW;
			break;

		case Entity::EntityObjectAction::NOTHING:
			action = Entity::EntityObjectAction::NOTHING;
			break;
		}

		if (action != Entity::EntityObjectAction::DELETE && action != Entity::EntityObjectAction::NOTHING)
		{
			ICollidable* icCast = dynamic_cast<ICollidable*>(entities.at(i));

			if (icCast != nullptr && 
				collide(projectiles, icCast)
				)
			{
				auto hCast = dynamic_cast<IHasHealth*>(entities.at(i));

				if (hCast == nullptr ||
						(hCast &&
						hCast->getHealth() == 0)
					)
				{
					delete entities.at(i);
					entities.erase(entities.begin() + i);
					i--;
				}
				else if (hCast != nullptr)
					hCast->damage();
			}

			data = entities.at(i)->tick();

			if (data.hasAttacked)
			{
				processAttack<T>(data.attack, *entities.at(i));
			}
		}
			
	}
}


template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::processAttack(EntityDataStorage::AttackID ID, T& entity)
{
	// TODO find out what this is supposed to do & what attackid is for
	/*ReturnData<EntityDataStorage::ProjectilePrototype> attack = EntityDataStorage::getAttack(ID);

	for (unsigned char i = 0; i < attack.COUNT; i++)
	{
		projectiles.emplace(new Projectile(ProjectilePrototype(attack.DATA[i]), &position));
	}*/
}

template <typename T, typename V> requires std::derived_from<T, ICollidable> && std::derived_from<V, ICollidable>
bool EntityManagementInterface::collide(std::vector<V*>& entities, T* entity)
{
	bool done = false;
	size_t index = 0;

	while (!done && index < entities.size())
	{
		if (dynamic_cast<ICollidable*>(entities[index])->collidesWith(entity) != ICollidable::CollisionType::MISS)
		{
			delete entities[index];
			entities.erase(entities.begin() + index);
			done = true;
		}
	}
	return done;
}


template<typename T> requires std::derived_from<T, Entity>
inline void EntityManagementInterface::generalLevelEditorUpdate(std::vector<T*> entities)
{
	// TODO fix
	/*
	for (Entity* entity : entities)
	{
		// if player clicking an entity
		if (entity->getSprite() != nullptr &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			entity->getSprite()->getGlobalBounds().intersects(sf::Mouse::getPosition())
		)
			std::cout << entity->getLine() << "\n";
	}*/

}