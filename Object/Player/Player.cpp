#include "Player.h"

Player::Player(short c, bool playerOne)
{
	isPlayerTwo = !playerOne;
	country = c;
	setSize(25, 50);
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
		switch (country * 8 + powerLevel * 2 + isPlayerTwo)
		{
		case 0:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(15, 12)));
			cooldown = 3;
			break;
		case 1:
			break;
		case 2:
			objects.push_back(new Projectile(pos.x, pos.y - 25, 
				sf::Vector2f(0, -10), sf::Vector2f(20, 14)));
			cooldown = 3;
			break;
		case 3:
			break;
		case 4:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(25, 15)));
			cooldown = 2;
			break;
		case 5:
			break;
		case 6:
			objects.push_back(new Projectile(pos.x, pos.y - 25,
				sf::Vector2f(0, -10), sf::Vector2f(32, 18)));
			cooldown = 2;
			break;
		case 7:
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
		switch (country * 2 + isPlayerTwo)
		{
		case 0: //Create mini nuke in the middle of the screen
			objects.push_back(new Projectile(winSize.x / 2, winSize.y / 2, 
				sf::Vector2f(0, 0), sf::Vector2f(winSize.x / 3, winSize.y / 3)
				, 1, true));
			cooldown = 30;
			break;
		case 1: //Rockets from bottom
			for (int i = 0; i < 8; i++)
			{
				objects.push_back(new Projectile(winSize.x / 8 * i, winSize.y,
				sf::Vector2f(0, -5), sf::Vector2f(18, 65), 0, true));
			}
			cooldown = 30;
			break;
		case 2: //Big laser that follows player
			if (movingProjectile == nullptr)
			{
				movingProjectile = new Projectile(pos.x, winSize.y / 2,
					sf::Vector2f(0, 0), sf::Vector2f(50, winSize.y)
					, 2, true);
				objects.push_back(movingProjectile);
				timer = 300;
				cooldown = 30;
			}
			break;
		case 3: //Stop time wave
			objects.push_back(new Projectile(pos.x, pos.y, 
			sf::Vector2f(0, 0), sf::Vector2f(1, 1), 3, true));
			cooldown = 30;
			break;
		case 4: //Tracking Rockets
			cooldown = 30;
			break;
		case 5: //Cluster Bomb?
			cooldown = 30;
			break;
		case 6: //Many nukes
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(75, 75), 1, true));
			cooldown = 30;
			break;
		case 7: //Missile Circle
			cooldown = 30;
			break;
		default:
			objects.push_back(new Projectile(pos, sf::Vector2f(0, -10),
			sf::Vector2f(40, 100)));
			cooldown = 30;
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

	if (timer > 0)
	{
		timer--;
		if (timer == 0)
			movingProjectile = nullptr;
	}

	if (!health)
	{
		//Disappear
		
	}

	nextFrame();
	
	objectUpdate(winSize, objects);
	
	if (movingProjectile != nullptr)
		movingProjectile->setPos(pos.x, winSize.y / 2);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
