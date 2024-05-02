#include "Player.h"

Player::Player(short c, bool playerOne, float* bgSpeed)
{
	backgroundSpeed = bgSpeed;
	isPlayerTwo = !playerOne;
	country = c;
	setSize(20, 32);
	type = PLAYER;
	health = 3; //Health is used for lives, the player dies in one hit.
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
		case 0: case 9: case 17: case 25: //Blob
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(11, 18), 0, true,
				0, 0));
			cooldown = 4;
			break;
		case 1: case 16: //Player 1 Sweden is the same as Player 2 America
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(9, 28), 0, true, 
				0, 4));
			cooldown = 4;
			break;
		case 2: case 11: case 19: case 27:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 30), 0, true,
				0, 1));
			cooldown = 4;
			break;
		case 3: case 18: //Rain
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 32), 0, true, 0, 5));
			cooldown = 4;
			break;
		case 4: case 13: case 21: case 29: 
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(31, 30), 0, true, 0, 2));
			cooldown = 3;
			break;
		case 5: case 20: 
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(41, 44), 0, true, 0, 6));
			cooldown = 4;
			break;
		case 6: case 15: case 23: case 31:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(47, 46), 0, true, 0, 3));
			cooldown = 4;
			break;
		case 7: case 22:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(64, 48), 0, true, 0, 7));
			cooldown = 4;
			break;
		case 8: //Japan 1, Shurikens
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), 0, true, 0, 8));
			cooldown = 4;
			break;
		case 10:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), 0, true, 0, 8));
			cooldown = 3;
			break;
		case 12: 
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), 0, true, 0, 8));
			cooldown = 3;
			break;
		case 14:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(9, 31), 0, true, 0, 9));
			cooldown = 3;
			break;
		case 24: //England 1, Big Blob
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(9, 31), 0, true, 0, 10));
			cooldown = 4;
			break;
		case 26:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 31), 0, true, 0, 11));
			cooldown = 4;
			break;
		case 28:
			for (int num = 0; num < 3; num++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(10 * cos((90 + 20 * (num - 1)) * PI / 180),
						-10 * sin((90 + 20 * (num - 1)) * PI / 180)),
					sf::Vector2f(9, 31), 0, true, 0, 10));
			}
			cooldown = 4;
			break;
		case 30:
			for (int num = 0; num < 3; num++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(10 * cos((90 + 20 * (num - 1)) * PI / 180),
						-10 * sin((90 + 20 * (num - 1)) * PI / 180)),
					sf::Vector2f(16, 31), 0, true, 0, 11));
			}
			cooldown = 4;
			break;
		default:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), sf::Vector2f(-2.6, -9.7),
			sf::Vector2f(32, 32), 0, true, 0, -1));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), sf::Vector2f(0, -10),
			sf::Vector2f(32, 32), 0, true, 0, -1));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), sf::Vector2f(2.6, -9.7),
			sf::Vector2f(32, 32), 0, true, 0, -1));
			cooldown = 4;
			break;
		}
	}
	//The secondary fire acts independently from the main fire and needs
	//it's own cooldown.
	if (!cooldownSecondary)
	{
		switch (country * 8 + powerLevel * 2 + isPlayerTwo)
		{
		case 4: case 6:
			for (int fireNum = 0; fireNum < 7; fireNum++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - fireNum * 35,
					sf::Vector2f(0, 0), sf::Vector2f(25, 35), 1, true, 10,
					10 * fireNum, -1));
			}
			cooldownSecondary = 23;
			break;
		case 5: case 7:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15), 4, true, 0, 18));
			cooldownSecondary = 15;
			break;
		case 12:
			for (int num = 0; num < 4; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(12, 12), 4, true, 0, 18));
			cooldownSecondary = 30;
			break;
		case 13: //Lasers
			objects.push_back(new Projectile(pos.x - 25, pos.y - (size.y / 2), sf::Vector2f(0, -25),
			sf::Vector2f(5, 50), 2, true, 0, -1));
			objects.push_back(new Projectile(pos.x + 25, pos.y - (size.y / 2), sf::Vector2f(0, -25),
			sf::Vector2f(5, 50), 2, true, 0, -1));
			cooldownSecondary = 15;
			break;
		case 14:
			for (int num = 0; num < 8; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(12, 12), 4, true, 0, 18));
			cooldownSecondary = 30;
			break;
		case 15:
			objects.push_back(new Projectile(pos.x - 25, pos.y - (size.y / 2), sf::Vector2f(0, -25),
				sf::Vector2f(5, 50), 2, true, 0, -1));
			objects.push_back(new Projectile(pos.x + 25, pos.y - (size.y / 2), sf::Vector2f(0, -25),
				sf::Vector2f(5, 50), 2, true, 0, -1));
			objects.push_back(new Projectile(pos.x - 50, pos.y - (size.y / 2), sf::Vector2f(0, -25),
				sf::Vector2f(5, 50), 2, true, 0, -1));
			objects.push_back(new Projectile(pos.x + 50, pos.y - (size.y / 2), sf::Vector2f(0, -25),
				sf::Vector2f(5, 50), 2, true, 0, -1));
			cooldownSecondary = 15;
			break;
		case 18:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), 0, true, 0, -1));
			cooldownSecondary = 5;
			break;
		case 19: //Tracking Mines
			for (int num = 0; num < 2; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15), 5, true, 100, -1));
			cooldownSecondary = 100;
			break;
		case 20:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), 0, true, 0, -1));
			cooldownSecondary = 5;
			break;
		case 21:
			for (int num = 0; num < 4; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15), 5, true, 100, -1));
			cooldownSecondary = 100;
			break;
		case 28: //Weird rockets
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), sf::Vector2f(0, -10),
			sf::Vector2f(12, 22), 2, true, 2000, 18));
			cooldownSecondary = 25;
			break;
		case 29: //Delayed nukes
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), 1, true, 20, 30, -1));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), 1, true, 20, 45, -1));
			cooldownSecondary = 35;
			break;
		case 30:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), sf::Vector2f(0, -10),
			sf::Vector2f(12, 22), 2, true, 2000, 18));
			cooldownSecondary = 25;
			break;
		case 31:
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), 1, true, 20, 30, -1));
			cooldownSecondary = 4;
			break;
		}
	}
}

//uses the special ability of the player based on what country the user selected
void Player::special(std::vector<Object*>& objects, sf::Vector2u winSize)
{
	if (!cooldown && specialCharge > 0)
	{
		specialCharge--;
		switch (country * 2 + isPlayerTwo)
		{
		case 0: //Create mini nuke in the middle of the screen
			objects.push_back(new Projectile(winSize.x / 2, winSize.y / 2, 
				sf::Vector2f(0, 0), sf::Vector2f(winSize.x / 3, winSize.y / 3)
				, 1, true, 120, 40, 1));
			cooldown = 120;
			cooldownSecondary = 120;
			break;
		case 1: //Rockets from bottom
			for (int i = 0; i < 16; i++)
			{
				objects.push_back(new Projectile(rand() % winSize.x, winSize.y - 33,
				sf::Vector2f(0, -5), sf::Vector2f(9, 65), 2, true, 15 * i, 10 * i, 1));
			}
			cooldown = 20;
			cooldownSecondary = 20;
			break;
		case 2: //Big laser that follows player
			if (timer == 0)
			{
				movingProjectile = new Projectile(pos.x, winSize.y / 2,
					sf::Vector2f(0, 0), sf::Vector2f(50, winSize.y)
					, 1, true, 300, 1);
				objects.push_back(movingProjectile);
				timer = 300;
				cooldown = 30;
				cooldownSecondary = 30;
			}
			break;
		case 3: //Stop time wave
			objects.push_back(new Projectile(pos.x, pos.y, 
			sf::Vector2f(0, 0), sf::Vector2f(1, 1), 3, true, 30, 1));
			cooldown = 80;
			cooldownSecondary = 80;
			cooldownTime = 300;
			break;
		case 4: //Tracking Rockets
			for (int num = 0; num < 8; num++)
			{
				objects.push_back(new Projectile(pos.x, pos.y,
					sf::Vector2f(0, -10), sf::Vector2f(8, 30), 4, true, 0, 18));
			}
			cooldown = 60;
			cooldownSecondary = 60;
			break;
		case 5: //Cluster Bomb
			for (int clusterNum = 0; clusterNum < 10; clusterNum++)
			{
				for(int xOffset = -1 * (clusterNum - 1); xOffset < clusterNum; xOffset++)
				objects.push_back(new Projectile(pos.x + xOffset * 30,
				pos.y - (clusterNum - abs(xOffset) - 1) * 60 - 30,
				sf::Vector2f(0, 0), sf::Vector2f(30, 60), 1, true, 30,
				20 * (clusterNum + 1), 1));
			}
			cooldown = 25;
			cooldownSecondary = 25;
			break;
		case 6: //Many nukes
			for(int i = 0; i < 8; i++)
			objects.push_back(new Projectile(rand() % winSize.x, rand() % winSize.y,
				sf::Vector2f(0, 0), sf::Vector2f(35, 35), 1, true, 100, 10 * i, 1));
			cooldown = 40;
			cooldownSecondary = 40;
			break;
		case 7: //Missile Circle
			for (int num = 0; num < 16; num++)
			{
				objects.push_back(new Projectile(pos.x + 80 * cos(num),
					pos.y + 80 * sin(num), sf::Vector2f(0, 0), sf::Vector2f(25, 25),
					1, true, 120, 30, 1));
			}
			cooldown = 40;
			cooldownSecondary = 40;
			break;
		default:
			objects.push_back(new Projectile(pos.x, pos.y, sf::Vector2f(0, -10),
			sf::Vector2f(40, 100), 0, true, 0, -1));
			cooldown = 120;
			cooldownSecondary = 120;
			break;
		}
	}
}

void Player::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	setSize(20, 32);
	//If the player is currently dead, don't do anything
	if (timerDeath)
	{
		setSize(0, 0);
		timerDeath--;
		return;
	}
	//If gone do nothing
	if (!health)
		return;
	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (((objects->at(i)->getType() == ENEMY_PROJECTILE)
			|| (objects->at(i)->getType() == AIR))
			&& this->intersect(objects->at(i))
			&& !invincibility)
		{
			health--;
			objects->push_back(new Explosion(pos, 0));
			objects->push_back(new Collectable(1, pos, backgroundSpeed));
			specialCharge = 2;
			if (rand() % 5 == 0)
				objects->push_back(new Collectable(2, pos, backgroundSpeed));
			if (!health)
			{
				if(rand() % 25 == 0)
					objects->push_back(new Collectable(3, pos, backgroundSpeed));
			}
			pos = sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.75f);
			invincibility = 61;
			timerDeath = 61;
			setSize(0, 0);
		}
		else if (objects->at(i)->getType() == COLLECTABLE && this->intersect(objects->at(i)))
		{
			switch (objects->at(i)->getID())
			{
			case 0: //Interact with money
				//Increase score
				break;
			case 1: //Interact with P
				if (powerLevel < 3)
					powerLevel++;
				else
				{
					//score increase by 2000
				}
				break;
			case 2: //Interact with B
				if (specialCharge < 5)
					specialCharge++;
				break;
			case 3: //Interact with F
				powerLevel = 3;
				break;
			}
		}
	}

	if (cooldown != 0)
		cooldown--;

	if (cooldownSecondary != 0)
		cooldownSecondary--;

	if (invincibility != 0)
		invincibility--;

	if (timer > 0)
	{
		timer--;
		if (timer <= 0)
			movingProjectile = nullptr;
	}

	if (cooldownTime != 0)
		cooldownTime--;

	objectUpdate(winSize, objects);

	if (movingProjectile != nullptr)
		movingProjectile->setPos(pos.x, pos.y - winSize.y / 2);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(health && !timerDeath)
		target.draw(sprite, states);
}

void Player::setHealth(short newHealth)
{
	health = newHealth;
}

short Player::getHealth()
{
	return health;
}

short Player::getSpecialCharge()
{
	return specialCharge;
}

//moves the player on the window
void Player::move(sf::Vector2u winSize)
{
	if (vel.x > 0)
		sideAnimation++;
	else if (vel.x < 0)
		sideAnimation--;
	else
	{
		if (sideAnimation > 0)
			sideAnimation--;
		else if (sideAnimation < 0)
			sideAnimation++;
	}
	if (sideAnimation > 14)
		sideAnimation = 14;
	if (sideAnimation < -14)
		sideAnimation = -14;

	// the dividing to an int is needed for the updates per frame delay.
	sprite.setTextureRect(sf::IntRect(
		texOffset.x + (sideAnimation / 5 + 2) * texSize.x * !verticalAnimation,
		texOffset.y + (sideAnimation / 5 + 2) * texSize.y * verticalAnimation,
		texSize.x, texSize.y));

	if (pos.x - size.x / 2.f < 0)
		pos.x = size.x / 2.f;
	if (pos.y - size.y / 2.f < 0)
		pos.y = size.y / 2.f;
	if (pos.x + size.x / 2.f >= winSize.x)
		pos.x = winSize.x - size.x / 2.f;
	if (pos.y + size.y / 2.f >= winSize.y)
		pos.y = winSize.y - size.y / 2.f;

	Object::move(winSize);
}

//This is to tell if time should be moving
bool Player::getTime()
{
	if (!cooldownTime)
		return true;
	return false;
}