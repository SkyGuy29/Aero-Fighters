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
void Player::shoot(std::vector<Object*>& objects)
{
	// cooldown is so a constant stream of projectiles isn't created
	if (!cooldown)
	{
		switch (country)
		{
		case -1:
			objects.push_back(new Projectile(pos, -15.f, 10.f));
			objects.push_back(new Projectile(pos,   0.f, 10.f));
			objects.push_back(new Projectile(pos,  15.f, 10.f));
			break;
		}
		cooldown = cooldownVal;
	}
}

void Player::special()
{
}

void Player::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == 3 && this->intersect(objects->at(i)))
		{
			setRandColor();
		}
	}

	if (cooldown)
		cooldown--;

	nextFrame();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
