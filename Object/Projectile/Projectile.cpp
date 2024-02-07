#include "Projectile.h"

Projectile::Projectile()
{
	 
}

Projectile::Projectile(sf::Vector2f pos, float angle, float vel)
{
	setSize(10, 4);
	setPos(pos);
	setRotation(angle);
	this->vel = vel;
}

Projectile::Projectile(float posX, float posY, float angle, float vel)
{
	setSize(10, 4);
	setPos(posX, posY);
	setRotation(angle);
	this->vel = vel;
}

void Projectile::update(sf::Vector2u winSize)
{
	move(std::sin(rot * TO_RAD) * vel, -std::cos(rot * TO_RAD) * vel, winSize);
}
