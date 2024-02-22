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

	if (outOfBounds(winSize))
		del = true;
}
