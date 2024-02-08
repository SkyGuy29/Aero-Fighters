#include "Projectile.h"

Projectile::Projectile()
{
	 
}

Projectile::Projectile(sf::Vector2f pos, float angle, float vel)
{
	setSize(4, 10);
	setPos(pos);
	setRotation(angle);
	this->vel = vel;
}

Projectile::Projectile(float posX, float posY, float angle, float vel)
{
	setSize(4, 10);
	setPos(posX, posY);
	setRotation(angle);
	this->vel = vel;
}

void Projectile::update(sf::Vector2u winSize)
{
	pos.x += std::sin(rot * TO_RAD) * vel;
	pos.y -= std::cos(rot * TO_RAD) * vel;

	sprite.setPosition(pos);

	if (outOfBounds(winSize))
		del = true;
}
