#include "EntityManagementInterface.h"

#include <assert.h>
#include <ranges>

#include "../../Entities/Enemy/Enemy.h"
#include "../../Entities/Player/Player.h"
#include "../../Entities/PowerUp/PowerUp.h"
#include "../../Entities/TileEntity/TileEntity.h"
#include "../../Entities/Enemy/Boss/Boss.h"
// must declare these in cpp
std::unordered_map<unsigned int, std::vector<EntityPrototype*>> EntityManagementInterface::spawnMap;
std::vector<Player*> EntityManagementInterface::players; // spawned at start
std::vector<Enemy*> EntityManagementInterface::landEnemies; // spawned at start (spawnMap:0)
std::vector<Projectile*> EntityManagementInterface::projectiles; // spawned dynamically by enemies
std::vector<Enemy*> EntityManagementInterface::airEnemies; // spawnMap
std::vector<Enemy*> EntityManagementInterface::waterEnemies; // spawnMap
std::vector<Boss*> EntityManagementInterface::bossEnemies; // ?
std::vector<TileEntity*> EntityManagementInterface::tileEntities; // spawned at start (spawnMap:0)
std::vector<PowerUp*> EntityManagementInterface::powerUps; // spawned dynamically by enemies
std::unordered_map<std::string, std::vector<ProjectilePrototype>> EntityManagementInterface::attackData;
unsigned int EntityManagementInterface::lastTick = -1; // max int (unsigned)


void EntityManagementInterface::load(Map map)
{
	players.push_back(new Player(sf::Vector2f(100, 100), Player::AMERICA, false));
	players.push_back(new Player(sf::Vector2f(150, 100), Player::AMERICA, true));
	loadAttacks();
	loadEnemies(map);
	EntityDataStorage::loadTextures();
}


void EntityManagementInterface::tick(sf::RenderWindow& win, unsigned int currentTick)
{
	// spawn the entities on the map with the current tick. Also make sure that we are not spawning enemies over and over if the tick is the same.
	if (spawnMap.contains(currentTick) && currentTick != lastTick)
	{
		std::vector<EntityPrototype*>& spawnableEntities = spawnMap[currentTick];
		for (EntityPrototype* entityPrototype : spawnableEntities)
		{
			if (entityPrototype->ID < EntityID::ENEMY_COUNT)
			{
				if (entityPrototype->ID < EntityID::ENEMY_AIR_COUNT)
					airEnemies.push_back(new Enemy(entityPrototype));
				else if (entityPrototype->ID < EntityID::ENEMY_LAND_COUNT)
					landEnemies.push_back(new Enemy(entityPrototype));
				else if (entityPrototype->ID < EntityID::ENEMY_WATER_COUNT)
					waterEnemies.push_back(new Enemy(entityPrototype));
			}
			else if (entityPrototype->ID < EntityID::TILE_ENTITY_COUNT)
				tileEntities.push_back(new TileEntity(entityPrototype));
		}
	}

	generalTick<Enemy>(landEnemies, win);
	generalTick<Projectile>(projectiles, win);
	generalTick<Player>(players, win);
	generalTick<Enemy>(airEnemies, win);
	generalTick<Enemy>(waterEnemies, win);
	generalTick<Boss>(bossEnemies, win);
	generalTick<TileEntity>(tileEntities, win);
	generalTick<PowerUp>(powerUps, win);
}


void EntityManagementInterface::updateLevelEditor()
{
	generalLevelEditorUpdate(tileEntities);
	generalLevelEditorUpdate(airEnemies);
	generalLevelEditorUpdate(waterEnemies);
	generalLevelEditorUpdate(landEnemies);
}


void EntityManagementInterface::unload()
{
	deleteVector((std::vector<void*>&)landEnemies);
	deleteVector((std::vector<void*>&)airEnemies);
	deleteVector((std::vector<void*>&)waterEnemies);
	deleteVector((std::vector<void*>&)bossEnemies);
	deleteVector((std::vector<void*>&)players);
	deleteVector((std::vector<void*>&)projectiles);
	deleteVector((std::vector<void*>&)tileEntities);
	deleteVector((std::vector<void*>&)powerUps);
	EntityDataStorage::unloadTextures();

	// deletes the prototypes in the spawn map
	for (auto& val : spawnMap | std::views::values)
		for (auto pPrototype : val)
			delete pPrototype;
}


inline void EntityManagementInterface::loadAttacks()
{
	std::ifstream f;
	f.open("res/attacks.txt");
	if (!f.is_open())
		throw std::runtime_error("Unable to load attacks file!");
	std::string input;
	struct TempData
	{
		sf::Vector2f spawnPos, spawnVelocity, hitboxSize;
		unsigned char tempId = 0;
		EntityID id;
		unsigned int tickOffset = 0;
		unsigned char flags = 0;
	};
	TempData tempData;
	std::string attackName;
	unsigned int line = 0;
	std::vector<float> splitVec;
	
	while (!f.eof())
	{
		input.clear();
		std::getline(f, input);

		// attacks are arrays of projectiles
		if (input.starts_with("NEW"))
		{
			attackName = input.substr(4, std::string::npos);
			attackData[attackName] = std::vector<ProjectilePrototype>();
		}
		else if (input.starts_with("PROJ"))
		{
			input = "";
			while(!input.starts_with("PROJ") && !f.eof())
			{
				std::getline(f, input);
				line++;
				if (input == ".")
					continue; // dont update the respective value
				switch(line)
				{
				case 1:
					splitVec = split_(input);
					assert(splitVec.size() == 2); // we want program execution to be stopped if we cant load the attack correctly
					tempData.spawnPos = sf::Vector2f(splitVec[0], splitVec[1]);
					break;
				case 2:
					splitVec = split_(input);
					assert(splitVec.size() == 2);
					tempData.spawnVelocity = sf::Vector2f(splitVec[0], splitVec[1]);
					break;
				case 3:
					tempData.id = EntityID((int)EntityID::PROJECTILE_START + atoi(input.c_str()) + 1);
					break;
				case 4:
					tempData.tickOffset = atoi(input.c_str());
					break;
				case 5:
					tempData.flags = atoi(input.c_str());
					break;
				case 6:
					splitVec = split_(input);
					assert(splitVec.size() == 2);
					tempData.hitboxSize = sf::Vector2f(splitVec[0], splitVec[1]);
				}
			}
			line = 0;
			if(!f.eof())
				f.seekg(-5, std::ios_base::cur); // setup for next read

			// id is an offset from the projectile start entity id
			attackData[attackName].emplace_back(tempData.spawnPos,
				tempData.spawnVelocity, tempData.id, tempData.tickOffset, tempData.flags
			);
		}
	}
}
/*
Work for importing attack data:
enum ProjectileType : unsigned char {
		Basic,
		TimerPierce,
		PierceOffscreen,
		JapanPlayer2Super,
		Tracking,
		SwedenPlayer2Mine,
		Breakable
	};

Projectile(float posX, float posY, sf::Vector2f vel,
		sf::Vector2f size, ProjectileType ID, bool player, short cool, short delay,
		short sprite, bool fromP1); //Adds delay
Projectile(float posX, float posY, sf::Vector2f vel,
		sf::Vector2f size, ProjectileType ID, bool player, short cool, short spriteNum, bool fromP1);

search for objects->push_back(new Projectile())

(attack example.txt)
*/


inline void EntityManagementInterface::loadEnemies(Map map)
{
	struct TempData
	{
		short id = 0;
		unsigned int spawnTick = 0;
		sf::Vector2f pos, vel;
		unsigned int line = 0;
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
		// TODO: verify that enemies.txt is valid (I dont think 0 or 1 id is right cause it is child!) (check coords of spawns)
		if(input.starts_with("NEW"))
		{
			f >> tempData.id >> tempData.pos.x >> tempData.pos.y >> tempData.vel.x >> tempData.vel.y;
			tempData.line += 6; // 5 + space
		}

		if (input == "NEW LAND")
			spawnMap[0].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)((int)EntityID::ENEMY_AIR_COUNT + tempData.id + 1), 0, tempData.line));
		else if (input == "NEW AIR") // TODO: Add water
		{
			f >> tempData.spawnTick;
			if(!spawnMap.contains(tempData.spawnTick))
				spawnMap[tempData.spawnTick] = std::vector<EntityPrototype*>();
			tempData.line += 1;
			spawnMap[tempData.spawnTick].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)tempData.id, 0, tempData.line));
		}
		else if (input == "NEW TILE")
			spawnMap[0].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)((int)EntityID::ENEMY_COUNT + tempData.id + 1), 0, tempData.line));
	}
}

/**
 * Loads children from children.txt with the following line based structure
 * 
 * ln# | Data
 * ----+-------------------------
 *  #1 | NEW comment
 *  #2 | Parent EntityID
 *  #3 | Total Children (uint8_t)
 *     +------ CHILD ARRAY ------
 *  #4 | Child EntityID
 *  #5 | Child:Parent X offset
 *  #6 | Child:Parent Y offset
 * ... | ...
 */
inline void EntityManagementInterface::loadChildren()
{
	// Stores the data needed to build the variable array of child data at runtime
	struct ChildBuildData
	{
		// ID of the parent and the children it owns
		struct ParentBlock
		{
			IDRead parent;
			unsigned char childCount = 0;
			EntityDataStorage::ChildTemplete* children = nullptr;
		};

		// The total children found
		unsigned char totalChildren = 0;

		// Each mapping from a parent to its respective children
		std::vector<ParentBlock> families;
	};
	ChildBuildData childData;

	// Input for comment checking; ignore the comment line
	std::string input, comment;

	// The file being read
	std::ifstream file;
	file.open("res/children.txt");

	// While the file is open and we have not reached the end
	while (file.is_open() && !file.eof())
	{
		input.clear();
		std::getline(file, input);

		// To appease andrews comment request *sigh*.
		if (input.starts_with("NEW"))
		{
			// Create a new parent
			childData.families.push_back(ChildBuildData::ParentBlock());

			// Reference for brevity
			ChildBuildData::ParentBlock* back = &(childData.families.back());

			// Load parent metadata
			file >> comment >> back->parent.in >> back->childCount;

			// Load all the parents child data
			for (unsigned char i = 0; i < back->childCount; i++)
			{
				// Allocate space for the children
				back->children = new EntityDataStorage::ChildTemplete[back->childCount];

				// Load current child metadata
				file >> back->children[i].ID.in >> back->children[i].parentOffset.x >> back->children[i].parentOffset.y;
			}
		}
	}
}


void EntityManagementInterface::deleteVector(std::vector<void*>& a)
{
	for (int i = 0; i < a.size(); i++)
		delete a[i];
	a.clear();
}