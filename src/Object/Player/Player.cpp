#include "Player.h"


Player::Player(const short country, const bool playerOne, float* bgSpeed)
{
	backgroundSpeed = bgSpeed;
	isPlayerTwo = !playerOne;
	this->country = country;
	setSize(20, 32);
	type = PLAYER;
	health = 3; //Health is used for lives, the player dies in one hit.
}


/// <summary>
/// takes a pointer from Level's ojects so it can add Projectiles to it.
/// </summary>
/// <param name="objects">Main object vector.</param>
void Player::shoot(std::vector<Object*>& objects)
{
	// cooldown is so a constant stream of projectiles isn't created
	// and doesn't trivialize the game.
	if (cooldown == 0)
	{
		switch (country * 8 + powerLevel * 2 + isPlayerTwo)
		//This switch statement produces the primary fire
		{
		//usa player 1 and all other country player 2s use this at base power level
		case 0: case 9: case 17: case 25: 
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(11, 18), ProjectileType::Basic,
				true, 0, 0, !isPlayerTwo));
			cooldown = 4;
			break;
		case 1: case 16: //Player 1 Sweden is the same as Player 2 America, base power level
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(9, 28), ProjectileType::Basic,
				true, 0, 4, !isPlayerTwo));
			cooldown = 4;
			break;
		case 2: case 11: case 19: case 27: //usa p1 power level 1 (0 is base)
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 30), ProjectileType::Basic,
				true, 0, 1, !isPlayerTwo));
			cooldown = 4;
			break;
		case 3: case 18: //sweden p1 power level 1
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 32), ProjectileType::Basic,
				true, 0, 5, !isPlayerTwo));
			cooldown = 4;
			break;
		case 4: case 13: case 21: case 29: //usa p1 power level 2
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(31, 30), ProjectileType::Basic,
				true, 0, 2, !isPlayerTwo));
			cooldown = 3;
			break;
		case 5: case 20: //sweden p1 power level 2
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(41, 44), ProjectileType::Basic,
				true, 0, 6, !isPlayerTwo));
			cooldown = 4;
			break;
		case 6: case 15: case 23: case 31: //usa p1 power level 3 (final)
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(47, 46), ProjectileType::Basic,
				true, 0, 3, !isPlayerTwo));
			cooldown = 4;
			break;
		case 7: case 22: //sweden p1 power level 3
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(64, 48), ProjectileType::Basic,
				true, 0, 7, !isPlayerTwo));
			cooldown = 4;
			break;
		case 8: //Japan p1, Shurikens
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), ProjectileType::Basic,
				true, 0, 8, !isPlayerTwo));
			cooldown = 4;
			break;
		case 10: //Shurikens power 1, increased spread (varied velocity) from base
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), ProjectileType::Basic,
				true, 0, 8, !isPlayerTwo));
			cooldown = 3;
			break;
		//identical to previous, the only difference should be missles.
		//i have 0 idea if that is what this actually does. - Christian
		case 12: 
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(15, 29), ProjectileType::Basic,
				true, 0, 8, !isPlayerTwo));
			cooldown = 3;
			break;
		case 14: //Kunai, japan p1 power 3
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -15), sf::Vector2f(9, 31), ProjectileType::Basic,
				true, 0, 9, !isPlayerTwo));
			cooldown = 3;
			break;
		case 24: //England player 1 base power level
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(9, 31), ProjectileType::Basic,
				true, 0, 10, !isPlayerTwo));
			cooldown = 4;
			break;
		case 26: //England p1 power 1
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(16, 31), ProjectileType::Basic,
				true, 0, 11, !isPlayerTwo));
			cooldown = 4;
			break;
		case 28: //uses same sprite as base power level england, but shoots in both diagonals too
			for (int num = 0; num < 3; num++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(10 * cos((90 + 20 * (num - 1)) * PI / 180),
						-10 * sin((90 + 20 * (num - 1)) * PI / 180)),
					sf::Vector2f(9, 31), ProjectileType::Basic, true, 0, 10, !isPlayerTwo));
			}
			cooldown = 4;
			break;
		case 30: //see case 28, same sprite as power level 1 england.
			for (int num = 0; num < 3; num++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(10 * cos((90 + 20 * (num - 1)) * PI / 180),
						-10 * sin((90 + 20 * (num - 1)) * PI / 180)),
					sf::Vector2f(16, 31), ProjectileType::Basic, true, 0, 11, !isPlayerTwo));
			}
			cooldown = 4;
			break;
		default: //Nothing should use this, but it's here just in case.
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), 
			sf::Vector2f(-2.6f, -9.7f),
			sf::Vector2f(32, 32), ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), 
			sf::Vector2f(0, -10),
			sf::Vector2f(32, 32), ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), 
			sf::Vector2f(2.6f, -9.7f),
			sf::Vector2f(32, 32), ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
			cooldown = 4;
			break;
		}
	}
	//The secondary fire acts independently from the main fire and needs
	//it's own cooldown.
	if (cooldownSecondary == 0)
	{
		switch (country * 8 + powerLevel * 2 + isPlayerTwo)
		{
		case 4: case 6: //Fire, usa p1
			for (int fireNum = 0; fireNum < 7; fireNum++)
			{
				objects.push_back(new Projectile(pos.x, pos.y - fireNum * 35,
					sf::Vector2f(0, 0), sf::Vector2f(25, 35), ProjectileType::TimerPierce, true, 10,
					10 * fireNum, -1, !isPlayerTwo));
			}
			cooldownSecondary = 23;
			break;
		case 5: case 7: //Rockets, usa p2 (NON HOMING IIRC)
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15), ProjectileType::Tracking, true, 0, 18, !isPlayerTwo));
			cooldownSecondary = 15;
			break;
		case 12: //japan homing rockets
			for (int num = 0; num < 4; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(0, -10), sf::Vector2f(12, 12),
					ProjectileType::Tracking, true, 0, 18, !isPlayerTwo));
			cooldownSecondary = 30;
			break;
		case 13: //Lasers (the white things, Christian knows), japan p2
			objects.push_back(new Projectile(pos.x - 25, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x + 25, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			cooldownSecondary = 15;
			break;
		case 14: //japan homing rockets (should just be more of them)
			for (int num = 0; num < 8; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
					sf::Vector2f(0, -10), sf::Vector2f(12, 12),
					ProjectileType::Tracking, true, 0, 18, !isPlayerTwo));
			cooldownSecondary = 30;
			break;
		case 15: //Lasers buff for japan p2, gets 4 prongs instead of 2
			objects.push_back(new Projectile(pos.x - 25, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x + 25, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x - 50, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x + 50, pos.y - (size.y / 2), 
				sf::Vector2f(0, -25), sf::Vector2f(5, 50),
				ProjectileType::PierceOffscreen, true, 0, -1, !isPlayerTwo));
			cooldownSecondary = 15;
			break;
		case 18: //sweden p1 non homing rockets
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
			cooldownSecondary = 5;
			break;
		case 19: //Tracking Mines sweden p2
			for (int num = 0; num < 2; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15),
					ProjectileType::SwedenPlayer2Mine, true, 100, -1, !isPlayerTwo));
			cooldownSecondary = 100;
			break;
		case 20: //sweden p1 non homing rocket buff, this may just be more missiles. not sure.
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
			cooldownSecondary = 5;
			break;
		case 21: //Tracking Mines 2, again i dont remember the difference - Christian
			for (int num = 0; num < 4; num++)
				objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(15, 15), ProjectileType::SwedenPlayer2Mine, true, 100, -1, !isPlayerTwo));
			cooldownSecondary = 100;
			break;
		case 28: //"Weird rockets" yeah thanks for the help, england p1
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), 
			sf::Vector2f(0, -10), sf::Vector2f(12, 22), ProjectileType::SwedenPlayer2Mine, true, 2000, 18, !isPlayerTwo));
			cooldownSecondary = 25;
			break;
		case 29: //Delayed nukes england p2
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(12, 22),
				ProjectileType::TimerPierce, true, 20, 30, -1, !isPlayerTwo));
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(12, 22),
				ProjectileType::TimerPierce, true, 20, 45, -1, !isPlayerTwo));
			cooldownSecondary = 35;
			break;
		case 30: //"Weird Rockets 2" england p1 buff
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2), 
				sf::Vector2f(0, -10), sf::Vector2f(12, 22),
				ProjectileType::PierceOffscreen, true, 2000, 18, !isPlayerTwo));
			cooldownSecondary = 25;
			break;
		case 31: //Delayed Nukes 2 england p2 buff
			objects.push_back(new Projectile(pos.x, pos.y - (size.y / 2),
				sf::Vector2f(0, -10), sf::Vector2f(12, 22),
				ProjectileType::TimerPierce, true, 20, 30, -1, !isPlayerTwo));
			cooldownSecondary = 4;
			break;
		}
	}
}

//uses the special ability of the player based on what country the user selected
void Player::special(std::vector<Object*>& objects, sf::Vector2f winSize)
{
	if (!(cooldown == 0 && specialCharge > 0))
		return;
	specialCharge--;
	switch (country * 2 + isPlayerTwo)
	{
	case 0: //Create mini nuke in the middle of the screen usa p1
		objects.push_back(new Projectile(winSize.x / 2, winSize.y / 2, 
			sf::Vector2f(0, 0), sf::Vector2f(winSize.x / 3, winSize.y / 3),
			ProjectileType::Basic, true, 120, 40, 1, !isPlayerTwo));
		cooldown = 120;
		cooldownSecondary = 120;
		break;
	case 1: //Rockets from bottom
		for (int i = 0; i < 16; i++)
		{
			objects.push_back(new Projectile((float)(rand() % (int)winSize.x), 
				winSize.y - 33,	sf::Vector2f(0, -5), sf::Vector2f(9, 65), 
				ProjectileType::PierceOffscreen, true, 15 * i, 10 * i, 1, !isPlayerTwo));
		}
		cooldown = 20;
		cooldownSecondary = 20;
		break;
	case 2: //Big laser that follows player japan p1
		if (timer == 0)
		{
			movingProjectile = new Projectile(pos.x, winSize.y / 2,
				sf::Vector2f(0, 0), sf::Vector2f(50, winSize.y),
				ProjectileType::TimerPierce, true, 300, 1, !isPlayerTwo);
			objects.push_back(movingProjectile);
			timer = 300;
			cooldown = 30;
			cooldownSecondary = 30;
		}
		break;
	case 3: //Stop time wave japan p2 (VIEWPORT GUYS PLEASE LOOK INTO THIS)
		objects.push_back(new Projectile(pos.x, pos.y, 
			sf::Vector2f(0, 0), sf::Vector2f(1, 1),
			ProjectileType::JapanPlayer2Super, true, 30, 1, !isPlayerTwo));
		cooldown = 80;
		cooldownSecondary = 80;
		cooldownTime = 300;
		break;
	case 4: //those BIG tracking Rockets sweden p1
		for (int num = 0; num < 8; num++)
		{
			objects.push_back(new Projectile(pos.x, pos.y,
				sf::Vector2f(0, -10), sf::Vector2f(8, 30),
				ProjectileType::Tracking, true, 0, 18, !isPlayerTwo));
		}
		cooldown = 60;
		cooldownSecondary = 60;
		break;
	case 5: //Cluster Bomb sweden p2
		for (int clusterNum = 0; clusterNum < 10; clusterNum++)
		{
			for(int xOffset = -1 * (clusterNum - 1); xOffset < clusterNum; 
			xOffset++)
			objects.push_back(new Projectile(pos.x + xOffset * 30,
				pos.y - (clusterNum - abs(xOffset) - 1) * 60 - 30,
				sf::Vector2f(0, 0), sf::Vector2f(30, 60),
				ProjectileType::TimerPierce, true, 30,
			20 * (clusterNum + 1), 1, !isPlayerTwo));
		}
		cooldown = 25;
		cooldownSecondary = 25;
		break;
	case 6: //Many nukes england p1
		for(int i = 0; i < 8; i++)
		objects.push_back(new Projectile((float)(rand() % (int)winSize.x), 
			(float)(rand() % (int)winSize.y), sf::Vector2f(0, 0), sf::Vector2f(35, 35), 
			ProjectileType::TimerPierce, true, 100, 10 * i, 1, !isPlayerTwo));
		cooldown = 40;
		cooldownSecondary = 40;
		break;
	case 7: //Missile Circle england p2
		for (int num = 0; num < 16; num++)
		{
			objects.push_back(new Projectile(pos.x + 80 * (float)cos(num),
				pos.y + 80 * (float)sin(num), sf::Vector2f(0, 0),
				sf::Vector2f(25, 25), ProjectileType::TimerPierce,
				true, 120, 30, 1, !isPlayerTwo));
		}
		cooldown = 40;
		cooldownSecondary = 40;
		break;
	default: //Just in case the switch statement fails.
		objects.push_back(new Projectile(pos.x, pos.y, 
			sf::Vector2f(0, -10), sf::Vector2f(40, 100),
			ProjectileType::Basic, true, 0, -1, !isPlayerTwo));
		cooldown = 120;
		cooldownSecondary = 120;
		break;
	}
}


/// <summary>
/// Updates the player.
/// </summary>
/// <param name="winSize"></param>
/// <param name="objects">Main object vector.</param>
/// <param name="time"></param>
void Player::update(const sf::Vector2f winSize, std::vector<Object*>* objects, bool time, int& p1Score, int& p2Score)
{
	setSize(20, 32);
	//If the player is currently dead, don't do anything
	if (timerDeath > 0)
	{
		setSize(0, 0);
		timerDeath--;
		return;
	}
	//If gone do nothing
	if (health == 0)
		return;
	//Am I being shot?
	for (unsigned int i = 0; i < objects->size(); i++)
	{
		if (((objects->at(i)->getType() == ENEMY_PROJECTILE)
			|| (objects->at(i)->getType() == AIR))
			&& this->intersect(objects->at(i))
			&& !invincibility)
		{
			//If the player is hit while not invincible
			health--;
			objects->push_back(new Explosion(pos, 0));
			objects->push_back(new Collectable(1, pos, backgroundSpeed));
			specialCharge = 2;
			if (rand() % 5 == 0)
				objects->push_back(new Collectable(2, pos, backgroundSpeed));
			if (health == 0)
			{
				if(rand() % 25 == 0)
					objects->push_back(new Collectable(3, pos, 
					backgroundSpeed));
			}
			pos = sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.75f);
			invincibility = 61;
			timerDeath = 61;
			setSize(0, 0);
		}
		else if (objects->at(i)->getType() == COLLECTABLE 
				&& this->intersect(objects->at(i)))
		{
			switch (objects->at(i)->getId())
			{
			case 0: //Interact with money
				//Increase score by 1000
				break;
			case 1: //Interact with P
				if (powerLevel < 3)
					powerLevel++;
				else
				{
					//score increase by 2000
				}
				break;
			case 2: //Interact with B powerup
				if (specialCharge < 5)
					specialCharge++;
				break;
			case 3: //Interact with F powerup
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

	Player::move(winSize);

	if (movingProjectile != nullptr)
		movingProjectile->setPos(pos.x, pos.y - winSize.y / 2);
}


void Player::updateBgSpeed(float* bgSpeed)
{
	backgroundSpeed = bgSpeed;
}


void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if(health && !timerDeath)
		target.draw(sprite, states);
}

//what just happened
void Player::setHealth(const short newHealth)
{
	health = newHealth;
}


short Player::getHealth() const
{
	return health;
}


short Player::getSpecialCharge() const
{
	return specialCharge;
}


//moves the player on the window
void Player::move(sf::Vector2f winSize)
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
	if (pos.y - size.y / 2.f < view.getCenter().y - view.getSize().y / 2.f)
		pos.y = view.getCenter().y - view.getSize().y / 2.f + size.y / 2.f;
	if (pos.x + size.x / 2.f >= view.getCenter().x + view.getSize().x / 2.f)
		pos.x = view.getCenter().x + view.getSize().x / 2.f - size.x / 2.f;
	if (pos.y + size.y / 2.f >= view.getCenter().y + view.getSize().y / 2.f)
		pos.y = view.getCenter().y + view.getSize().y / 2.f - size.y / 2.f;

	vel.y -= *backgroundSpeed;

	Object::move(winSize);
}


//This is to tell if time should be moving
bool Player::getTime() const
{
	if (cooldownTime == 0)
		return true;
	return false;
}

//reading all of this code makes me want to cave my skull in