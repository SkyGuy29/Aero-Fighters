#include "Projectile.h"

Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}

//id 0 is basic projectiles
//id 1 is for projectiles on a timer that pierce
//id 2 is for projectiles that pierce and go off screen
//id 3 is for Japan Player 2's super
//id 4 is for tracking projectiles
//id 5 is the tracking mines of Sweden Player 2
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player, short cool, short sprit)
{
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	setSpriteNum(sprit);
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool;
}


//Use when you want to delay the projectiles spawn
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short dela, short sprit)
{
	delay = dela;
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	setSpriteNum(sprit);
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool + dela;
}

//The bulk of projectiles, all it does is move and check when to die.
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	nextFrame(1);
	if (delay)
	{
		size = sf::Vector2f(0, 0);
		delay--;
		if (!delay)
			size = tempSize;
	}

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
	float closestEnemyDistance = 350;

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
		float angle = atan(-vel.y / vel.x);
		std::cout << angle << std::endl;
		if (vel.x < 0)
			angle += PI;
		angle += (PI / 6); //Consuming ten billion years in an instant.
		std::cout << angle << std::endl;
		vel = sf::Vector2f(5 * cos(angle), -5 * sin(angle));
	}
	objectUpdate(winSize, objects);
}