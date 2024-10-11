#include "EntityManagementInterface.h"
#include "../../Entities/Enemy/Enemy_new.h"
#include "../../Entities/Player/Player_new.h"
#include "../../Entities/PowerUp/PowerUp.h"
#include "../../Entities/Spawner/PermanentSpawner/PermanentSpawner.h"
#include "../../Entities/Spawner/TemporarySpawner/TemporarySpawner.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss_new.h"

void EntityManagementInterface::tick(sf::RenderWindow& win)
{
	generalTick<Enemy_new>(landEnemies, win);
	for (auto land : landEnemies)
	{
		
	}

	generalTick<Enemy_new>(airEnemies, win);
	for (auto air : airEnemies)
	{
		
	}

	generalTick<Enemy_new>(waterEnemies, win);
	for (auto water : waterEnemies )
	{

	}

	generalTick<Boss_new>(bossEnemies, win);
	for (auto boss : bossEnemies)
	{

	}

	generalTick<Projectile_new>(projectiles, win);
	for (auto projectile : projectiles)
	{

	}

	generalTick<PermanentSpawner>(permanentSpawners, win);
	for (auto permSpawner : permanentSpawners)
	{

	}

	generalTick<TemporarySpawner>(temporarySpawners, win);
	for (auto tempSpawner : temporarySpawners)
	{

	}

	generalTick<TileEntity>(tileEntities, win);
	for (auto tile : tileEntities)
	{

	}

	generalTick<PowerUp>(powerUps, win);
	for (auto powerUp : powerUps)
	{

	}
}