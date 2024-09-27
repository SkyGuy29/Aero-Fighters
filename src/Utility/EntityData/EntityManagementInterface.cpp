#include "EntityManagementInterface.h"

void EntityManagementInterface::tick()
{
	for (auto land : landEnemies)
	{
		
	}

	for (auto air : airEnemies)
	{
		
	}

	for (auto water : waterEnemies )
	{

	}

	for (auto boss : bossEnemies)
	{

	}

	for (auto projectile : projectiles)
	{

	}

	for (auto permSpawner : permanentSpawners)
	{

	}

	for (auto tempSpawner : temporarySpawners)
	{

	}

	for (auto tile : tileEntities)
	{

	}

	for (auto powerUp : powerUps)
	{

	}
}

void EntityManagementInterface::draw(sf::RenderWindow& win)
{
}

void EntityManagementInterface::generalTick(Entity* entity)
{
	Entity::EntityObjectAction act = entity->getEntityAction();

	if (act == Entity::EntityObjectAction::DELETE && !Level::levelEditorActive())
	{
		delete e[i];
		e.erase(e.begin() + i);
	}
	else if (act == Entity::EntityObjectAction::DRAW)
	{
		e[i]->tick();
		window.draw(*e[i]->getSprite());
	}
	// else do nothing
}
