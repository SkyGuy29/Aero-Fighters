#include "EntityManagementInterface.h"
#include "../../Entities/Enemy/Enemy_new.h"
#include "../../Entities/Player/Player_new.h"
#include "../../Entities/PowerUp/PowerUp.h"
#include "../../Entities/Spawner/PermanentSpawner/PermanentSpawner.h"
#include "../../Entities/Spawner/TemporarySpawner/TemporarySpawner.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss_new.h"


void EntityManagementInterface::tick(sf::RenderWindow& win, unsigned int currentTick)
{
	// spawn the entities on the map with the current tick.
	if (spawnMap.count(currentTick))
	{
		std::vector<EntityPrototype*>& spawnableEntities = spawnMap[currentTick];
		for (EntityPrototype* entityPrototype : spawnableEntities)
		{
			if (entityPrototype->ID < EntityID::ENEMY_COUNT)
			{
				if (entityPrototype->ID < EntityID::ENEMY_AIR_COUNT)
					airEnemies.push_back(new Enemy_new(entityPrototype));
				else if (entityPrototype->ID < EntityID::ENEMY_LAND_COUNT)
					landEnemies.push_back(new Enemy_new(entityPrototype));
				else if (entityPrototype->ID < EntityID::ENEMY_WATER_COUNT)
					waterEnemies.push_back(new Enemy_new(entityPrototype));
			}
			else if (entityPrototype->ID < EntityID::TILE_ENTITY_COUNT)
				tileEntities.push_back(new TileEntity(entityPrototype));
		}
	}

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


inline void EntityManagementInterface::loadAttacks()
{
	std::ifstream f;
	f.open("res/attacks.txt");
	if (!f.is_open())
		throw std::exception("Unable to load attacks file!");
	std::string input;
	struct TempData
	{
		sf::Vector2f spawnPos, spawnVelocity;
		unsigned char tempId;
		EntityID id;
		unsigned int tickOffset;
		unsigned char flags;
	};
	TempData tempData;
	
	
	while (!f.eof())
	{
		input.clear();
		std::getline(f, input);

		// attacks are arrays of projectiles
		if (input == "NEW")
			attackData.push_back(std::vector<ProjectilePrototype>());
		else if (input == "PROJ")
		{
			f >> tempData.spawnPos.x >> tempData.spawnPos.y
				>> tempData.spawnVelocity.x >> tempData.spawnVelocity.y
				>> tempData.tempId >> tempData.tickOffset >> tempData.flags;
			tempData.id = (EntityID)tempData.tempId;

			attackData[attackData.size()].push_back(ProjectilePrototype(tempData.spawnPos,
				tempData.spawnVelocity, tempData.id, tempData.tickOffset, tempData.flags)
			);
		}
	}
}


inline void EntityManagementInterface::loadEnemies(Map map)
{
	struct TempData
	{
		short id;
		unsigned int spawnTick;
		sf::Vector2f pos, vel;
	};
	TempData tempData;
	std::string input;
	
	std::ifstream f;
	f.open("res/" + mapStrings[map] + "/enemies.txt");

	/*
		The enemy knows where it is at all times.
		It knows this because it knows where it isn't.
		By subtracting where it is from where it isn't,
		or where it isn't from where it is (whichever is greater),
		it obtains a difference, or deviation.
		The guidance subsystem uses deviations to generate
		corrective commands to drive the missile from a position
		where it is to a position where it isn't,
		and arriving at a position where it wasn't, it now is.
		Consequently, the position where it is,
		is now the position that it wasn't,
		and it follows that the position that it was,
		is now the position that it isn't.
		In the event that the position that it is in is not
		the position that it wasn't, the system has acquired a variation,
		the variation being the difference between where the enemy is,
		and where it wasn't.
		If variation is considered to be a significant factor,
		it too may be corrected by the GEA.
		However, the enemy must also know where it was.
		The enemy guidance computer scenario works as follows.
		Because a variation has modified some of the information
		the enemy has obtained, it is not sure just where it is.
		However, it is sure where it isn't, within reason,
		and it knows where it was.
		It now subtracts where it should be from where it wasn't,
		or vice-versa, and by differentiating this from the
		algebraic sum of where it shouldn't be, and where it was,
		it is able to obtain the deviation and its variation,
		which is called error.
	*/
	
	spawnMap[0] = std::vector<EntityPrototype*>();
	// loading the enemies
	while (f.is_open() && !f.eof())
	{
		input.clear();
		std::getline(f, input);

		if (input == "NEW LAND")
		{
			spawnMap[0].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)tempData.id, 0));
		}
		else if (input == "NEW WATER" || input == "NEW AIR")
		{
			if(!spawnMap.count(tempData.spawnTick))
				spawnMap[tempData.spawnTick] = std::vector<EntityPrototype*>();
			// TODO: CLEAN THIS UP ON PROGRAM CLOSE (memory leaks rn)
			spawnMap[tempData.spawnTick].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)tempData.id, 0));
		}
	}
}