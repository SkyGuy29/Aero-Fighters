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


enum Map : uint8_t
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


	static void load(Map map, PlayerCountry country);
	static void tick(sf::RenderWindow& win, unsigned int currentTick);
	static void draw(sf::RenderWindow& win);
	static void updateLevelEditor();
	static std::vector<Player*>& getPlayers() { return players; }
	
	// frees memory
	static void unload();


	static void resetPlayers()
	{
		for (auto player : players)
		{
			player->setHealth(3);
		}
	}

private:
	static inline void loadAttacks();
	static inline void loadEnemies(Map map);
	static inline void loadChildren(VariableArray<EntityDataStorage::ChildTemplete> * arr);

	template<typename T> requires std::derived_from<T, Entity> 
	static void generalTick(std::vector<T*>& entities, sf::RenderWindow& win);

	template<typename T> requires std::derived_from<T, Entity>
	static void generalDraw(std::vector<T*>& entities, sf::RenderWindow& win);

	// note: attack strings can be found in attacks.txt after the NEW decleration for each attack
	template<typename T> requires std::derived_from<T, Entity>
	static void processAttack(std::string ID, T& entity);

	template<typename T> requires std::derived_from<T, Entity>
	static void generalLevelEditorUpdate(std::vector<T*> entities);

	template <typename T> requires std::derived_from<T, ICollidable>
	static bool collide(std::vector<Projectile*>& entities, T* entity);

	static void deleteVector(std::vector<void*>& a);

	// converts a string a player country
	static PlayerCountry strtoPC(std::string s);

	// helper function for splitting a string of doubles delimited by spaces
	static std::vector<float> split_(std::string s)
	{
		std::vector<float> ret;
		std::string temp;

		for (unsigned int i = 0; i < s.size(); i++)
		{
			if (s[i] == ' ')
			{
				ret.push_back(strtof(temp.c_str(), nullptr));
				temp.clear();
			}
			else
				temp += s[i];
		}
		ret.push_back(strtof(temp.c_str(), nullptr));

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
	//  map[powerLevel][player1/2][country]->string(full string)
	// subsequent maps must be pointers or else they die with the function call (maybe)
	// ^ for attacktree

	static unsigned int lastTick;
};


template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::generalDraw(std::vector<T*>& entities, sf::RenderWindow& win)
{
	for (unsigned short i = 0; i < entities.size(); i++)
	{
		if (entities.at(i)->getSprite() != nullptr)
			win.draw(*entities.at(i)->getSprite()); // TODO: ENSURE NO OUT OF BOUNDS
	}
}

template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::generalTick(std::vector<T*>& entities, sf::RenderWindow& win)
{
	Entity::EntityObjectAction action = Entity::EntityObjectAction::NOTHING;
	Entity::TickData data;

	// For every entity in the vector
	for (unsigned short i = 0; i < entities.size(); i++)
	{
		action = entities.at(i)->getEntityAction();
		switch(action)
		{
		case Entity::EntityObjectAction::DELETE:
			delete entities.at(i);
			entities.erase(entities.begin()+i);
			i--;
			break;
		case Entity::EntityObjectAction::DRAW:
		case Entity::EntityObjectAction::NOTHING:
			break;
		}

		 // todo add draw/ define action / stuff (tick dont tick)
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

			data = Entity::TickData(false, "");
			if(!entities.empty())
				data = entities.at(i)->tick();

			if (data.hasAttacked)
				processAttack<T>(data.attack, *entities.at(i));
		}
			
	}
}


template <typename T> requires std::derived_from<T, Entity>
void EntityManagementInterface::processAttack(std::string ID, T& entity)
{
	std::vector<ProjectilePrototype> prototypes = Entity::attackMap[ID];

	for (unsigned int i = 0; i < prototypes.size(); i++)
	{
		projectiles.push_back(new Projectile(prototypes[i], &entity, players[0]));
		projectiles[projectiles.size() - 1]->getEntityAction(); // force it to generate velocity, sprite, etc.
	}
}


template <typename T> requires std::derived_from<T, ICollidable>
bool EntityManagementInterface::collide(std::vector<Projectile*>& entities, T* entity)
{
	bool done = false;
	size_t index = 0;
	ICollidable::CollisionType collision;

	while (!done && index < entities.size())
	{
		collision = dynamic_cast<ICollidable*>(entity)->collidesWith(entities[index]);

		if (collision != ICollidable::CollisionType::MISS)
		{
			std::cout << "WAH\n";
			if (collision == ICollidable::CollisionType::HIT)
			{
				if (dynamic_cast<IHasHealth*>(entity) == nullptr)
					done = true;
				else
				{
					IHasHealth* healthEntity = (IHasHealth*)entity;
					healthEntity->damage();
					if (healthEntity->getHealth() == 0)
						done = true;
				}
			}

			delete entities[index];
			entities.erase(entities.begin() + index);
			done = true;
		}

		index++;
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