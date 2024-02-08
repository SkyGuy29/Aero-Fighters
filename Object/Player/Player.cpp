#include "Player.h"

Player::Player()
{
	cooldownVal = 2;
	vel = 5.f;
	setSize(25, 50);
	
	//setRandColor();
	animation.set(10, &sprite, "Res/animatorTest.png");
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
