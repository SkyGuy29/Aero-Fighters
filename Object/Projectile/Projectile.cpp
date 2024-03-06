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

Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player)
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
	if (id == 1)
		cooldown = 300;
	else if (id == 2)
		cooldown = 120;
	else if (id == 3)
		cooldown = 30; //Mao Mao's projectile
	//id 4 is for piercing projectiles
	//id 5 is for tracking projectiles
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short dela)
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
	if (id == 1) //For the different types of projectiles
		cooldown = 300 + dela;
	else if (id == 2)
		cooldown = 120 + dela;
	else if (id == 3) //Mao Mao's special
		cooldown = 30; 
	//id 4 is for piercing projectiles
	//id 5 is for tracking projectiles
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
		sprite.setSize(size);
		delay--;
	}

	if (delay == 0)
	{
		size = tempSize;
		sprite.setSize(size);
	}

	objectUpdate(winSize, objects);

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
	}
}
