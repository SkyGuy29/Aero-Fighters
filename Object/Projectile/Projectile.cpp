#include "Projectile.h"

Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f vel)
{
	setSize(4, 10);
	setPos(pos);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel)
{
	setSize(4, 10);
	setPos(posX, posY);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f size)
{
	setSize(size);
	setPos(pos);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel, sf::Vector2f size)
{
	setSize(size);
	setPos(posX, posY);
	this->vel = vel;
	type = PLAYER_PROJECTILE;
}

Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player)
{
	id = ID;
	setSize(size);
	setPos(posX, posY);
	this->vel = vel;
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	if (id = 1)
		cooldown = 90;
}

// Just moves in a straight line
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	// | comment if you hate rainbows |
	// V							  V

	// I think rainbows are pretty cool -Gabe
	// Rainbows are fine -Matthew

	objectUpdate(winSize, objects);

	setRandColor();

	sprite.setPosition(pos);

	if (id = 1)
		cooldown--;

	if (!cooldown)
		del = true;

	if (outOfBounds(winSize))
		del = true;

	for (int i = 0; i < objects->size(); i++)
	{
		if (type == PLAYER_PROJECTILE
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
