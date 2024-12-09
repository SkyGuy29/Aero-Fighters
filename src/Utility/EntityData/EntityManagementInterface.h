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

	/**
	 * Loads all data relating to the specified map and player country
	 *
	 * @param map The map being loaded
	 * @param country The country for the players
	 */
	static void load(Map map, PlayerCountry country);

	/**
	 * Spawns all entities for the tick and ticks all entities
	 *
	 * @param win The window for drawing
	 * @param currentTick The current tick number for spawning
	 */
	static void tick(sf::RenderWindow& win, unsigned int currentTick);

	/**
	 * Draws all entities
	 * 
	 * @param win The window used for drawing
	 */
	static void draw(sf::RenderWindow& win);

	/**
	 * Level Editor tick method
	 */
	static void updateLevelEditor();

	/**
	 * @todo Convert to array of 2? there can be at most 2 players.
	 *
	 * Gets the vector of players for external use
	 *
	 * @return The vector of players
	 */
	static std::vector<Player*>& getPlayers() { return players; }

	/**
	 * Unloads and deletes the entities and textures
	 */
	static void unload();

	/**
	 * Resets the health of both players
	 */
	static void resetPlayers()
	{
		for (auto player : players)
		{
			player->setHealth(3);
		}
	}

private:
	/**
	 * Loads all the attacks used by various entities including enemies and players
	 */
	static inline void loadAttacks();

	/**
	 * Loads all the enemy spawn order for this map
	 * 
	 * @param map The target map
	 */
	static inline void loadEnemies(Map map);

	/**
	 * Loads all the parent to child array mappings
	 *
	 * @param arr An array of all child templates
	 */
	static inline void loadChildren(VariableArray<EntityDataStorage::ChildTemplete> * arr);


	/**
	 * Deletes the specified element in the vector
	 *
	 * @tparam T The type held by the vector
	 * @param i The external array index
	 * @param vec The vector
	 */
	template<typename T>
	static inline void delElement(unsigned short& i, std::vector<T>& vec)
	{
		delete vec.at(i);
		vec.erase(vec.begin() + i);
		i--;
	}

	/**
	 * Handles generic tick processes for the provided entity vector
	 *
	 * @tparam T The type held by the entity vector
	 * @param entities The vector of the entities being ticked
	 * @param win The window used for drawing
	 */
	template<typename T> requires std::derived_from<T, Entity> 
	static void generalTick(std::vector<T*>& entities, sf::RenderWindow& win);

#pragma message("WARNING! Entities that do not need to be drawn will be drawn! : EntityManagementInterface::generalDraw<T>(std::vector<T*>&, sf::RenderWindow&)")
	/**
	 * Handles drawing for all entities
	 *
	 * @tparam T The type held by the vector
	 * @param entities The vector of entities being drawn
	 * @param win The window used for drawing
	 */
	template<typename T> requires std::derived_from<T, Entity>
	static void generalDraw(std::vector<T*>& entities, sf::RenderWindow& win);

	/**
	 * Spawns all projectiles for the specified attack
	 *
	 * @note attack strings can be found in attacks.txt after the NEW declaration for each attack
	 *
	 * @tparam T The type for the entity
	 * @param ID The attack ID
	 * @param entity The attacking entity
	 */
	template<typename T> requires std::derived_from<T, Entity>
	static void processAttack(std::string ID, T& entity);

	/**
	 * General level editor update for the specified entities
	 *
	 * @tparam T The type for the entities being passed
	 * @param entities The vector of entities being processed
	 */
	template<typename T> requires std::derived_from<T, Entity>
	static void generalLevelEditorUpdate(std::vector<T*> entities);

	/**
	 * Handles collision between a specified entity and all projectiles
	 * @warning Will kill the projectile that was collided with
	 *
	 * @tparam T The type of the entity being passed
	 * @param entities The Projectiles being passed
	 * @param entity The entity being checked
	 * @return If the entity has been collided with
	 */
	template <typename T> requires std::derived_from<T, ICollidable>
	static bool collide(std::vector<Projectile*>& entities, T* entity);

	/**
	 * Deleted all objects pointed to in the vector and clears it
	 *
	 * @param a The vector being passed
	 */
	static void deleteVector(std::vector<void*>& a);

	// 
	/**
	 * Converts a string a player country
	 *
	 * @param s The string being converted
	 * @return a PlayerCountry with the generated country
	 */
	static PlayerCountry strtoPC(std::string s);

	/**
	 * @todo returns floats? not doubles?
	 * helper function for splitting a string of doubles delimited by spaces
	 *
	 * @param s The string being processed
	 * @return A vector of all the floats
	 */
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
		{
			win.draw(*entities.at(i)->getSprite()); // TODO: ENSURE NO OUT OF BOUNDS

			sf::RectangleShape hitbox(entities.at(i)->getSprite()->getLocalBounds().getSize());
			hitbox.setPosition(entities.at(i)->getPosition() - hitbox.getSize() / 2.f);
			hitbox.setFillColor(sf::Color::Transparent);
			hitbox.setOutlineColor(sf::Color::Red);
			hitbox.setOutlineThickness(1);
			win.draw(hitbox);
		}
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
		// Get this entities action
		action = entities.at(i)->getEntityAction();
		
		// If this entity needs to be deleted
		if (action == Entity::EntityObjectAction::DELETE)
		{
			std::cout << "WE DIE - DEL?\n";
			// Delete it
			delElement(i, entities);
		}

		 // todo add draw/ define action / stuff (tick dont tick)
		 // 
		 // ToDo make conform with contract that collide specifies;
		 //      The entities themselves and their children are killed by collide;
		 //      The only remaining entity to be killed is the projectiles, not the entities

		if (action != Entity::EntityObjectAction::DELETE && action != Entity::EntityObjectAction::NOTHING)
		{
			// Cast to ICollidable to check if this entity can be hit
			ICollidable* icCast = dynamic_cast<ICollidable*>(entities.at(i));

			// If there are projectiles, this entity is collidable, and it is colliding with any projectiles
			if (projectiles.size() != 0 && icCast != nullptr && 
				collide(projectiles, icCast)
				)
			{
				// Try to cast it to check if it has health
				auto hCast = dynamic_cast<IHasHealth*>(entities.at(i));

				// If it doesnt have health or it does and its health is at 0
				if (hCast == nullptr ||
				   (hCast != nullptr && hCast->getHealth() == 0))
				{
					// Kill it
					std::cout << "WE DIE3\n";
					delElement(i, entities);
				} // Else damage it; It logically must have health
				else
					hCast->damage();
			}

			// Default data
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
	// Kill / Done
	uint8_t completion_flags = 0b00000000;
	size_t index = 0;
	ICollidable::CollisionType collision;

	while (!(completion_flags & 0b00000001) && index < entities.size())
	{
		collision = dynamic_cast<ICollidable*>(entity)->collidesWith(entities[index]);

		if (collision != ICollidable::CollisionType::MISS)
		{
			// Set 'Done' flag
			completion_flags |= 0b00000001;

			// If we hit it
			if (collision == ICollidable::CollisionType::HIT)
			{
				// If this entity has health, just damage it, else kill it.
				if (dynamic_cast<IHasHealth*>(entity) != nullptr)
				{
					IHasHealth* healthEntity = (IHasHealth*)entity;
					healthEntity->damage();
					if (healthEntity->getHealth() == 0)
						completion_flags |= 0b00000010;
				}
				else
					completion_flags |= 0b00000010;

				// If we need to kill the projectile
				if (completion_flags & 0b00000010)
				{
					std::cout << "WE DIE2\n";
					delete entities[index];
					entities.erase(entities.begin() + index);
					--index;
				}
			} // Otherwise the child was handled by the parent
		}

		index++;
	}
	return (completion_flags & 0b00000001);
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