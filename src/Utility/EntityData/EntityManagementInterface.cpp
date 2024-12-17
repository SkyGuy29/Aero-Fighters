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
unsigned int EntityManagementInterface::lastTick = -1; // max int (unsigned)



void EntityManagementInterface::load(Map map, PlayerCountry country)
{
	players.push_back(new Player(sf::Vector2f(100, 100), country, false));
	players.push_back(new Player(sf::Vector2f(150, 100), country, true));
	loadAttacks();
	loadEnemies(map);
	//Entity::setAttackMap(attackData);
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

// Draw order
// Last = top
// First = bottom or covered
void EntityManagementInterface::draw(sf::RenderWindow& win)
{
	generalDraw<Enemy>(landEnemies, win);
	generalDraw<Enemy>(waterEnemies, win);

	// These are like buildings, right?
	generalDraw<TileEntity>(tileEntities, win);

	generalDraw<Boss>(bossEnemies, win);
	generalDraw<Enemy>(airEnemies, win);

	generalDraw<PowerUp>(powerUps, win);
	generalDraw<Player>(players, win);
	generalDraw<Projectile>(projectiles, win);
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
	{
		for (auto pPrototype : val)
		{
			delete pPrototype;
			pPrototype = nullptr;
		}
		val.clear(); // to ensure not using garbage data
	}
		
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
			Entity::attackMap[attackName] = std::vector<ProjectilePrototype>();
		}
		else if (input.starts_with("PROJ"))
		{
			input = "";
			while(!input.starts_with("NEW") && !input.starts_with("PROJ") && !f.eof())
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
					tempData.spawnVelocity = sf::Vector2f(splitVec[0], splitVec[1]); // here checky why velocity dont work
					break;
				case 3:
					tempData.id = EntityID((int)EntityID::PROJECTILE_START + atoi(input.c_str()) + 1 );
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
				f.seekg((long long)-1 * (signed long long)input.size()-2, std::ios_base::cur); // setup for next read

			// id is an offset from the projectile start entity id
			Entity::attackMap[attackName].emplace_back(tempData.spawnPos,
				tempData.spawnVelocity, tempData.id, tempData.tickOffset, tempData.flags
			);
		}
	}

	// now that attacks are loaded into a workable format, we load it into the Player attack tree.
	/* algo:
		 * filter "O" + std::to_string(powerLevel) -> array L
		 * search L for "P" + (isPlayerTwo ? "2" : "1")
		 * if found->grab the attack from attack map and return the tick data.
		 * else, throw an error noting that attack was unable to be found.
		 *
		 * attack tree: map[powerLevel][player1/2][country]->string(full string)
		 */
	// ex: O0_P1AMERICA_P2ENGLAND_P2JAPAN_P2SWEDEN
	for(auto& it : Entity::attackMap)
	{
		if (!(it.first.starts_with("O0") || it.first.starts_with("O1") ||
			it.first.starts_with("O2") || it.first.starts_with("O3"))
			) // we must do all cause what if an attack just starts with O w/o being a player attack
			continue;
		const std::string& attack = it.first;
		short powerLevel = (short)strtol(attack.substr(1, 1).c_str(), nullptr, 0);
		assert(powerLevel <= 3 && powerLevel >= 0);
		PlayerCountry country;
		bool isPlayerTwo;
		std::string split;

		for(int i = 3; i <= attack.size(); i++)
		{
			if (attack[i] == '_' || i == attack.size())
			{
				assert(split.substr(1, 1) == "1" || split.substr(1, 1) == "2");
				if (split.substr(1, 1) == "1")
					isPlayerTwo = false;
				else
					isPlayerTwo = true;
				country = strtoPC(split.substr(2, std::string::npos));
				// std::unordered_map<unsigned short, std::unordered_map<bool, std::unordered_map<PlayerCountry, std::string>>>
				if(!Entity::playerAttackTree.contains(powerLevel))
					Entity::playerAttackTree[powerLevel] = std::unordered_map<bool, std::unordered_map<PlayerCountry, std::string>>();

				if(!Entity::playerAttackTree.at(powerLevel).contains(isPlayerTwo))
					Entity::playerAttackTree[powerLevel][isPlayerTwo] = std::unordered_map<PlayerCountry, std::string>();

				Entity::playerAttackTree.at(powerLevel).at(isPlayerTwo)[country] = attack; // todo: ensure this works without using heap data
				split.clear();
			}
			else
				split.push_back(attack[i]);
		}
	}
	if (true) {};
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
			spawnMap[0].push_back(new EntityPrototype(tempData.pos, tempData.vel, (EntityID)((int)EntityID::ENEMY_COUNT + tempData.id + 2), 0, tempData.line));
	}
}

/**
 * Loads children from children.txt with the following line based structure
 * 
 * ln# | Data
 * ----+------------------------------------+
 *  #1 | 'NEW' comment                      |
 *  #2 | Parent EntityID                    |
 *  #3 | Total Stages (uint8_t)             |
 *     +------- STAGE ARRAY --------------+ |
 *     |                                  | |
 *     +------- START STAGE ------------+ | |
 *  #4 | Total Children (uint8_t)       | | |
 *     +------- CHILD ARRAY ----------+ | | |
 *     |                              | | | |
 *     +------- START CHILD --------+ | | | |
 *  #5 | Child EntityID             | | | | |
 *  #6 | Child:Parent X offset      | | | | |
 *  #7 | Child:Parent Y offset      | | | | |
 *     |                            | | | | |
 *     +-------- END CHILD ---------+ | | | |
 * ... | ... More children            | | | |
 *     |                              | | | |
 *     +----- END CHILD ARRAY --------+ | | |
 *     +-------- END STAGE -------------+ | |
 * ... | ... More stages                  | |
 *     |                                  | |
 *     +----- END STAGE ARRAY ------------+ |
 * ... | ... More parents                   |
 * ----+------------------------------------+
 */
/*
inline void EntityManagementInterface::loadChildren(VariableArray<VariableArray<EntityDataStorage::ChildTemplete>>* arr)
{
	// Stores the data needed to build the variable array of child data at runtime
	struct ChildBuildData
	{
		// ID of the parent and the children it owns
		struct ParentBlock
		{
			struct StageData
			{
				unsigned char childCount = 0;
				unsigned char childStartingIndex = 0;
				EntityDataStorage::ChildTemplete* children = nullptr;
			};

			IDRead parent;
		};

		// The total children found
		unsigned short totalChildren = 0;

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
			childData.families.emplace_back(ChildBuildData::ParentBlock());

			// Reference for brevity
			ChildBuildData::ParentBlock* back = &(childData.families.back());

			// Update starting index for VariableArray building
			back->childStartingIndex = childData.totalChildren;

			// Load parent metadata
			file >> comment >> back->parent.in >> back->childCount;

			// Load all the parents child data
			for (unsigned char i = 0; i < back->childCount; i++)
			{
				// Increment the total found children
				++childData.totalChildren;
				// Allocate space for the children
				back->children = new EntityDataStorage::ChildTemplete[back->childCount];

				// Load current child metadata
				file >> back->children[i].ID.in >> back->children[i].parentOffset.x >> back->children[i].parentOffset.y;
			}
		}
	}

	//##### Convert to variable array #####//
	
	// Allocate data for raw children
	auto* rawData = new EntityDataStorage::ChildTemplete[childData.totalChildren];
	auto* spacing = new SpacingElement[childData.families.size()];
	unsigned short currentChild = 0;

	// Place every single child here
	// theres a word for this, nursery I think. could be daycare
	// make sure all children are cared for, no more piles, Ricky.
	// next time I will call CPS
	for (unsigned char i = 0; i < childData.families.size(); i++)
	{
		spacing[i] = SpacingElement(childData.families.at(i).childStartingIndex, childData.families.at(i).childStartingIndex + childData.families.at(i).childCount);

		for (unsigned char i = 0; i < childData.families.at(i).childCount; i++)
		{
			rawData[currentChild] = childData.families.at(i).children[i];
			++currentChild;
		}
	}

	arr = new VariableArray<EntityDataStorage::ChildTemplete>(rawData, spacing, childData.families.size());

	for (auto& parent : childData.families)
	{
		delete parent.children;
	}
}*/


void EntityManagementInterface::deleteVector(std::vector<void*>& a)
{
	for (int i = 0; i < a.size(); i++)
		delete a[i];
	a.clear();
}

PlayerCountry EntityManagementInterface::strtoPC(std::string s)
{
	PlayerCountry ret;


	if (s == "AMERICA")
		ret = PlayerCountry::AMERICA;
	else if (s == "SWEDEN")
		ret = PlayerCountry::SWEDEN;
	else if (s == "JAPAN")
		ret = PlayerCountry::JAPAN;
	else if (s == "ENGLAND")
		ret = PlayerCountry::ENGLAND;
	else
		throw std::runtime_error("Invalid string passed to strtoPC.");

	return ret;
}
