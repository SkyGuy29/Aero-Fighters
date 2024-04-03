#include "Projectile.h"

Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}

//id 0 is basic projectiles
//id 1 is for projectiles on a timer that pierce
//id 2 is for projectiles that pierce and go off screen
//id 3 is Mao Mao's super
//id 4 is for tracking projectiles
//id 5 is the tracking mines of sweden
//The best generic Projectile constructor
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player, short cool, int sprit)
{
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	spriteNum = sprit;
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool;
}


//Use when you want to delay the projectiles spawn
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short dela, int sprit)
{
	delay = dela;
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	spriteNum = sprit;
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool + dela;
}

// Just moves in a straight line
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	// | comment if you hate rainbows |
	// V							  V

	// I think rainbows are pretty cool -Gabe
	// Rainbows are fine -Matthew


	//Make groups of three projectiles that are stacked vertically
	//The Kunai is the sole exception which should be on it's own.
	//Stack them in the order of America Player 1 projectile,
	//America Player 2 projectile, Japan Player 1 projectile,
	//England Player 1 projectile.

	if (delay)
	{
		size = sf::Vector2f(0, 0);
		delay--;
	}

	if (!delay)
	{
		if(id != 3)
			size = tempSize;
		objectUpdate(winSize, objects);
	}

	nextFrame();

	if (id == 3)
	{
		setRandColor();
		setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setOrigin(sprite.getSize() / 2.f);
	}

	if (id && cooldown)
		cooldown--;

	if (!cooldown && id && (id < 4) && (id != 2))
		del = true;

	if (outOfBounds(winSize))
		del = true;

	Object* closestEnemy = nullptr;
	float newEnemyDistance;
	float closestEnemyDistance = 999999999999;

	for (int i = 0; i < objects->size(); i++)
	{
		if (type == PLAYER_PROJECTILE
			&& (!id || id >= 4)
			&& ((objects->at(i)->getType() == AIR
				|| objects->at(i)->getType() == LAND)
				&& this->intersect(objects->at(i))))
		{
			del = true;
		}
		else if (type == ENEMY_PROJECTILE
			&& objects->at(i)->getType() == PLAYER
			&& this->intersect(objects->at(i)))
		{
			del = true;
		}
		if (id >= 4 && (objects->at(i)->getType() == AIR
			|| objects->at(i)->getType() == LAND)
			&& objects->at(i)->shouldDelete() == false)
		{
			newEnemyDistance = sqrt((objects->at(i)->getPos().x - pos.x)
				* (objects->at(i)->getPos().x - pos.x) + (objects->at(i)->getPos().y - pos.y)
				* (objects->at(i)->getPos().y - pos.y));
			if (closestEnemyDistance > newEnemyDistance)
			{
				closestEnemyDistance = newEnemyDistance;
				closestEnemy = objects->at(i);
			}

		}
	}
	if (closestEnemy != nullptr)
	{
		vel = sf::Vector2f( 5 * (closestEnemy->getPos().x - pos.x) / closestEnemyDistance,
		5 * (closestEnemy->getPos().y - pos.y) / closestEnemyDistance);
	}
	else if (id == 5)
	{
		//Doesn't spin correctly
		std::cout << "Turning\n";
		float angle = atan(vel.y / vel.x);
		angle += PI / 36;
		vel = sf::Vector2f(5 * cos(angle), -5 * sin(angle));
	}
}