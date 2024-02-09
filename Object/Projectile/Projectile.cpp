#include "Projectile.h"

Projectile::Projectile()
{
	type = 3;
}

Projectile::Projectile(sf::Vector2f pos, float angle, float vel)
{
	setSize(4, 10);
	setPos(pos);
	setRotation(angle);
	this->vel = vel;
	type = 3;
}

Projectile::Projectile(float posX, float posY, float angle, float vel)
{
	setSize(4, 10);
	setPos(posX, posY);
	setRotation(angle);
	this->vel = vel;
	type = 3;
}

// Just moves in a straight line
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	// | comment if you hate rainbows |
	// V							  V

	// I think rainbows are pretty cool -Gabe

	setRandColor();

	pos.x += std::sin(rot * TO_RAD) * vel;
	pos.y -= std::cos(rot * TO_RAD) * vel;

	sprite.setPosition(pos);

	if (outOfBounds(winSize))
		del = true;
}
