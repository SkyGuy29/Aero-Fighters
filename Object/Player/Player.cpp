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
	int offset = 0;
	// cooldown is so a constant stream of projectiles isn't created
	if (!cooldown)
	{
		switch (country * 4 + powerLevel)
		{
		case 0:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(15, 12)));
			cooldown = 3;
			break;
		case 1:
			objects.push_back(new Projectile(pos.x, pos.y - 25, 
				sf::Vector2f(0, -10), sf::Vector2f(20, 14)));
			cooldown = 3;
			break;
		case 2:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(25, 15)));
			cooldown = 2;
			break;
		case 3:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(32, 18)));
			cooldown = 2;
			break;
		default:
			objects.push_back(new Projectile(pos, sf::Vector2f(-2.6, -9.7)));
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10)));
			objects.push_back(new Projectile(pos, sf::Vector2f(2.6, -9.7)));
			cooldown = 3;
			break;
		}
	}
}

void Player::special(std::vector<Object*>& objects, sf::Vector2u winSize)
{
	if (specialCharge > 0 && !cooldown)
	{
		specialCharge--;
		switch (country)
		{
		case 0:
			objects.push_back(new Projectile(winSize.x / 2, winSize.y / 2, 
				sf::Vector2f(0, 0), sf::Vector2f(winSize.x / 3, winSize.y / 3)
				, 1, true));
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
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
				if(powerLevel < 3)
					powerLevel++;
				break;
			case 2: //Interact with B
				if(specialCharge < 5)
					specialCharge++;
				break;
			case 3: //Interact with F
				powerLevel = 3;
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
