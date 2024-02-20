#include "Player.h"

Player::Player()
{
	setSize(25, 50);
	frameCount = 10;
	type = PLAYER;
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
			objects.push_back(new Projectile(pos, sf::Vector2f(-2.6, -9.7)));
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10)));
			objects.push_back(new Projectile(pos, sf::Vector2f(2.6, -9.7)));
			break;
		}
		cooldown = 3;
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
		if (objects->at(i)->getType() == ENEMY_PROJECTILE && this->intersect(objects->at(i)))
		{
			setRandColor();
		}
	}

	if (cooldown)
		cooldown--;

	nextFrame();
	
	objectUpdate(winSize, objects);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
