#include "Player.h"

Player::Player()
{
	cooldownVal = 3;
	vel = 5.f;
	setSize(25, 50);
	
	animation.set(10, &sprite, "Res/animatorTest.png");
}

void Player::setProjectiles(std::vector<Projectile*>* p)
{
	projs = *p;
}

void Player::shoot()
{
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

	animation.next();

	for (int i = 0; i < projs.size(); i++)
	{
		projs[projs.size() - 1 - i]->update(winSize);
		if (projs[projs.size() - 1 - i]->shouldDelete())
		{
			delete projs[projs.size() - 1 - i];
			projs.erase(projs.end() - 1 - i);
		}
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
