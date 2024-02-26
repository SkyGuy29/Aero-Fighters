#include "Player.h"

Player::Player()
{
	setSize(25, 50);
	frameCount = 10;
	type = PLAYER;
	health = 3; //Health is used for lives.
}

// takes a pointer from Level's playerProjs so it can add Projectiles to it.
void Player::shoot(std::vector<Object*>& objects)
{
	// cooldown is so a constant stream of projectiles isn't created
	if (!cooldown)
	{
		switch (powerLevel * 4 + country)
		{
		case 0:
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10)));
			break;
		default:
			objects.push_back(new Projectile(pos, sf::Vector2f(-2.6, -9.7)));
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10)));
			objects.push_back(new Projectile(pos, sf::Vector2f(2.6, -9.7)));
			break;
		}
		cooldown = 3;
	}
}

void Player::special(std::vector<Object*>& objects)
{
	if (specialCharge > 0 && !cooldown)
	{
		switch (country)
		{
		default:
			specialCharge--;
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10),
			sf::Vector2f(40, 100)));
			cooldown = 10;
			break;
		}
	}
}

void Player::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{

	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if ((objects->at(i)->getType() == ENEMY_PROJECTILE) 
			|| (objects->at(i)->getType() == AIR)
			&& this->intersect(objects->at(i))
			&& !invincibility)
		{
			health--;
			pos = sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.75f);
			invincibility = 30;
		}
		else if (objects->at(i)->getType() == COLLECTABLE && this->intersect(objects->at(i)))
		{
			switch (objects->at(i)->getID())
			{
			case 0: //Interact with money
				//Increase score
				break;
			case 1: //Interact with P
				powerLevel++;
				break;
			case 2: //Interact with B
				specialCharge++;
				break;
			case 3: //Interact with F
				powerLevel = 5;
				break;
			}
		}
	}

	if (cooldown)
		cooldown--;

	if (invincibility)
		invincibility--;

	if (!health)
	{
		//Disappear
		type = -1;
	}

	nextFrame();
	
	objectUpdate(winSize, objects);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
