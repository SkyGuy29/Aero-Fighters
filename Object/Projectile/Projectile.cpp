#include "Projectile.h"

Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f vel)
{
	setSize(4, 10);
	tempSize = size;
	sprite.setSize(sf::Vector2f(4, 10));
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(pos);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel)
{
	setSize(4, 10);
	tempSize = size;
	sprite.setSize(sf::Vector2f(4, 10));
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f size)
{
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(pos);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel, sf::Vector2f size)
{
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

//id 0 is basic projectiles
//id 1 is for projectiles on a timer that dont disappear when they hit an enemy
//id 2 is for projectiles that pierce and go off screen
//id 3 is Mao Mao's projectile
//id 4 is for tracking projectiles
//The best generic Projectile constructor
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player, short cool)
{
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool;
	
}


//Use when you want to delay the projectiles spawn
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short dela)
{
	delay = dela;
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool + dela;
}

// Just moves in a straight line
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	// | comment if you hate rainbows |
	// V							  V

	// I think rainbows are pretty cool -Gabe
	// Rainbows are fine -Matthew

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

	sprite.setSize(size);

	setRandColor();

	sprite.setPosition(pos);

	if (id == 3)
	{
		setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setOrigin(sprite.getSize() / 2.f);
	}

	if (id && cooldown)
		cooldown--;

	if (!cooldown && id)
		del = true;

	if (outOfBounds(winSize))
		del = true;

	Object* closestEnemy = nullptr;
	float newEnemyDistance;
	float closestEnemyDistance = 999999999999;

	for (int i = 0; i < objects->size(); i++)
	{
		if (type == PLAYER_PROJECTILE
			&& !id
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
		if (id == 4 && (objects->at(i)->getType() == AIR 
			|| objects->at(i)->getType() == LAND)
			&& objects->at(i)->shouldDelete() == false)
		{
			newEnemyDistance = sqrt(objects->at(i)->getSize().x 
			* objects->at(i)->getSize().x + objects->at(i)->getSize().y
			* objects->at(i)->getSize().y);
			if (closestEnemyDistance > newEnemyDistance)
			{
				closestEnemyDistance = newEnemyDistance;
				closestEnemy = objects->at(i);
			}
			
		}
		if (closestEnemy != nullptr)
		{
			vel = sf::Vector2f((closestEnemy->getPos().x - pos.x) / closestEnemyDistance,
			(closestEnemy->getPos().y - pos.y) / closestEnemyDistance);
		}
	}
}
