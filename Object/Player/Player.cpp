#include "Player.h"

Player::Player()
{
	cooldownVal = 3;
	vel = 5.f;
	setSize(25, 50);
	frameCount = 10;
	type = 0;
}

// takes a pointer from Level's playerProjs so it can add Projectiles to it.
void Player::shoot(std::vector<Projectile*>& projs)
{
	// cooldown is so a constant stream of projectiles isn't created
	if (!cooldown)
	{
		switch (country)
		{
		case -1:
			projs.push_back(new Projectile(pos, -15.f, 10.f));
			projs.push_back(new Projectile(pos,   0.f, 10.f));
			projs.push_back(new Projectile(pos,  15.f, 10.f));
			break;
		}
		cooldown = cooldownVal;
	}
}

void Player::special()
{
}

void Player::update(sf::Vector2u winSize)
{
	if (cooldown)
		cooldown--;

	nextFrame();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
