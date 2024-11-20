#include "Enemy.h"  


Enemy::Enemy(sf::Vector2f pos, sf::Vector2f vel,
             EntityID ID, unsigned int line) :
	Entity(pos, ID), IHasHealth(ID)
{
	this->line = line;
}


Enemy::~Enemy()
{

}

Entity::TickData Enemy::tick()
{
	if (hasSpawned())
	{
		move();
		// Process next animation frame - subject to change
		nextFrame(3);

		/*
		hello this is Christian i STILL have no clue what i am doing
		once again i dont even know what the old enemy system does so this is gonna be rough
		right now im just spamming what i think needs to be done in here because "make enemy move and shoot" isnt enough

		first how do we even determine what enemy it is
		second what attack pattern is needed and how do i code that
		land.cpp and air.cpp in old should have some stuff

		Ricky or Andrew if you see this: HELP I HAVE NO IDEA WHAT TO DO HERE HOW DO I USE YOUR CODE
		*/

		switch (ID)
		{
		case EntityID::ENEMY_AIR_THICK_HELI_GREEN:
			break;
		case EntityID::ENEMY_AIR_THICK_HELI_RED:
			break;
		case EntityID::ENEMY_AIR_THIN_HELI_GREEN:
			break;
		case EntityID::ENEMY_AIR_THIN_HELI_RED:
			break;
		case EntityID::ENEMY_AIR_PLANE_1_GREEN:
			break;
		case EntityID::ENEMY_AIR_PLANE_1_RED:
			break;
		case EntityID::ENEMY_AIR_PLANE_2_BLUE:
			break;
		case EntityID::ENEMY_AIR_PLANE_2_GREEN:
			break;
		case EntityID::ENEMY_AIR_PLANE_2_RED:
			break;
		case EntityID::ENEMY_AIR_CHILD_CHOPPER_BLADES_SMALL:
			break;
		case EntityID::ENEMY_AIR_CHILD_CHOPPER_BLADES_BIG:
			break;
		case EntityID::ENEMY_AIR_ADVANCED_MEGACOPTOR:
			break;
		case EntityID::ENEMY_AIR_BIG_HELICOPTOR:
			break;
		case EntityID::ENEMY_AIR_BIG_PLANE_ANGLED:
			break;
		case EntityID::ENEMY_AIR_BIG_PLANE_STRAIGHT:
			break;
		case EntityID::ENEMY_AIR_PLANE_SPIN_SIDE_GREEN:
			break;
		case EntityID::ENEMY_AIR_PLANE_SPIN_SIDE_RED:
			break;
		case EntityID::ENEMY_AIR_PLANE_BACKFLIP_GREEN:
			break;
		case EntityID::ENEMY_AIR_PLANE_BACKFLIP_RED:
			break;
		case EntityID::ENEMY_AIR_COUNT:
			break;
		case EntityID::ENEMY_LAND_CHILD_TANK_WEAK_TOP_GREEN:
			break;
		case EntityID::ENEMY_LAND_CHILD_TANK_STRONG_TOP_GREEN:
			break;
		case EntityID::ENEMY_LAND_TANK_BOTTOM_GREEN:
			break;
		case EntityID::ENEMY_LAND_CHILD_TANK_WEAK_TOP_YELLOW:
			break;
		case EntityID::ENEMY_LAND_CHILD_TANK_STRONG_TOP_YELLOW:
			break;
		case EntityID::ENEMY_LAND_TANK_BOTTOM_YELLOW:
			break;
		case EntityID::ENEMY_LAND_TURRET_GREEN:
			break;
		case EntityID::ENEMY_LAND_TURRET_BLUE:
			break;
		case EntityID::ENEMY_LAND_TURRET_GRAY:
			break;
		case EntityID::ENEMY_LAND_SPACE_MINE:
			break;
		case EntityID::ENEMY_LAND_DESTROYED_TANK_GREEN:
			break;
		case EntityID::ENEMY_LAND_DESTROYED_TANK_YELLOW:
			break;
		case EntityID::ENEMY_LAND_COUNT:
			break;
		case EntityID::ENEMY_WATER_COUNT:
			break;
		case EntityID::ENEMY_COUNT:
			break;
		default:
			break;
		}

		if (curCooldown > 0)
			--curCooldown;
	}
	return TickData();
}

/*
Old code
void Enemy::enemyUpdate(const sf::Vector2f winSize, std::vector<Object*>* objects, int& p1Score, int& p2Score)
{
	texInit = false;
	objectUpdate(winSize, objects);
	nextFrame(3);

	if ((outOfTopBounds(winSize) == false && outOfBottomBounds(winSize) == false)  || levelEditor)
		entered = true;

	//Delete an enemy when it goes off screen
	if (outOfBottomBounds(winSize) == true)
		del = true;

	//
	// Go to spawn place
	// If the enemy has not yet entered the screen,
	// Knows the backgrounds position,
	// and the background is showing the enemies spawn position
	if (!entered && backgroundDist != nullptr && *backgroundDist <= startMark)
	{
		// Spawn the enemy by setting its position and velocity
		pos = spawnPos;
		if(!levelEditor)
			vel = spawnVel;
	}

	//Am I being shot?
	// For every entity
	for (int i = 0; i < objects->size(); i++)
	{
		// If the entity is a players projectile, is colliding with me, is not hidden, and is active
		if (objects->at(i)->getType() == PLAYER_PROJECTILE
			&& this->intersect(objects->at(i)) && type != HIDDEN
			&& entered)
		{
			// Decrement my health
			health--;

			// Very hacky way to increase score
			// I'm sorry, but also not
			if (((Projectile*)(objects->at(i)))->isFromP1())
				p1Score += 100;
			else
				p2Score += 100;
			objects->at(i)->setPos(-100, -100);
		}
	}


	// Generates Collectable items when an enemy dies, presumably dropped items. - ricky
	// If i'm dead, not scheduled to be deleted, and not hidden
	if (health <= 0 && del == false && type != HIDDEN)
	{
		// Drop powerups based on my specific type
		switch (id)
		{
			// If i'm a ___
		case 1:
			// If i'm an Air ___
			if (type == AIR)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

		// If i'm a ___
		case 2:
			// If i'm a land ___
			if(type == LAND)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

		//If i'm an ___
		case 8:
			// If i'm a land ___
			if(type == LAND)
				objects->push_back(new Collectable(0, pos, backgroundSpeed));
			del = true;
			break;

		// Otherwise do nothing
		default:
			del = true;
			break;
		}

		// Then spawn an explosion on my position
		objects->push_back(new Explosion(pos, 0));
	}
}
*/

Entity::TickData Enemy::attack()
{
	// Map IDs to attacks here, return information.
	return TickData();
}
