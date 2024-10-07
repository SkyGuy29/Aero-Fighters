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
	for (auto land : landEnemies)
	{
		generalTick(land);
	}

	for (auto air : airEnemies)
	{
		generalTick(air);
	}

	for (auto water : waterEnemies)
	{
		generalTick(water);
	}

	for (auto boss : bossEnemies)
	{
		generalTick(boss);
	}

	for (auto projectile : projectiles)
	{
		generalTick(projectile);
	}

	for (auto permSpawner : permanentSpawners)
	{
		generalTick(permSpawner);
	}

	for (auto tempSpawner : temporarySpawners)
	{
		generalTick(tempSpawner);
	}

	for (auto tile : tileEntities)
	{
		generalTick(tile);
	}

	for (auto powerUp : powerUps)
	{
		generalTick(powerUp);
	}
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
