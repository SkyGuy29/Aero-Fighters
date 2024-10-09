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
		short type, id;
		int startMark;
		sf::Vector2f pos, vel;
		std::fstream file;
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

	// loading the enemies
	while (f.is_open() && !f.eof())
	{
		input.clear();
		std::getline(f, input);

		if (input == "NEW LAND")
		{
			new Land_new(pos, vel, (EntityID)id, &backgroundSpeed);
		}
		else if (input == "NEW WATER")
		{
			
		}
		else if (input == "NEW AIR")
		{
			
		}
	}
	//I am so sorry -Gabe
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
