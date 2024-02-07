#include "Player.h"

Player::Player()
{
	setSize(25, 50);
	setRandColor();
}

Player::Player(sf::Vector2f pos, sf::Vector2u winSize)
{
	setSize(25, 50);
	setPos(pos);
	setRandColor();

	//animation.set(1, &sprite);
}

Player::Player(float posX, float posY, sf::Vector2u winSize)
{
	setSize(25, 50);
	setPos(posX, posY);
	setRandColor();

	//animation.set(1, &sprite);
}

void Player::shoot()
{
	switch (country)
	{
	case -1:
		projs.push_back(new Projectile());
		break;
	}
}

void Player::update(sf::Vector2u winSize)
{
	animation.next();
}
