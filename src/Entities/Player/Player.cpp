#include "Player.h"
std::vector<std::string> attacks;


Player::Player(sf::Vector2f pos, PlayerCountry country, bool isPlayerTwo) :
	Entity(pos, EntityID::PLAYER), IHasHealth(ID)
{
	setHealth(3);
	this->isPlayerTwo = isPlayerTwo;
	if(attacks.empty())
		for (auto& it : attackMap)
			attacks.push_back(it.first);
	this->country = country;
}

void Player::move()
{
	/*if (vel.x > 0)
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
		texSize.x, texSize.y));*/

	// bounds checking
	if (pos.x - getBounds().width / 2.f < 0)
		pos.x = getBounds().width / 2.f;
	if (pos.y - getBounds().height / 2.f < getView()->getCenter().y - getView()->getSize().y / 2.f)
		pos.y = getView()->getCenter().y - getView()->getSize().y / 2.f + getBounds().height / 2.f;
	if (pos.x + getBounds().width / 2.f >= getView()->getCenter().x + getView()->getSize().x / 2.f)
		pos.x = getView()->getCenter().x + getView()->getSize().x / 2.f - getBounds().width / 2.f;
	if (pos.y + getBounds().height / 2.f >= getView()->getCenter().y + getView()->getSize().y / 2.f)
		pos.y = getView()->getCenter().y + getView()->getSize().y / 2.f - getBounds().height / 2.f;

	getBounds().intersects(sf::IntRect(0,0, windowSize.width, windowSize.height));
	vel.y -= getBackgroundSpeed();

	Entity::move();
}


Entity::TickData Player::shoot()
{
	if (curCooldown != 0)
		return TickData(false, "");
	return TickData(true, playerAttackTree[powerLevel][isPlayerTwo][country]);
}


Entity::TickData Player::fireSpecial()
{
	return Entity::TickData();
}


Entity::TickData Player::tick()
{
	// controller controls
	// works with 2 controllers

	// Move Offset
	sf::Vector2f moveOffset;

	// If the player should shoot
	bool shoot, special;
	bool spawn;
	if (curCooldown != 0)
		curCooldown--;

	if (cooldownSecondary != 0)
		cooldownSecondary--;

	if (invincibility != 0)
		invincibility--;

	if (sf::Joystick::isConnected(isPlayerTwo))
	{
		moveOffset = joystick(isPlayerTwo);

		shoot = button(isPlayerTwo, Controller::Y);
		special = button(isPlayerTwo, Controller::B);

		spawn = button(isPlayerTwo, Controller::A);
	}
	else
	{
		moveOffset.x = (float)key(isPlayerTwo, Controls::Right) - key(isPlayerTwo, Controls::Left);
		moveOffset.y = (float)key(isPlayerTwo, Controls::Back) - key(isPlayerTwo, Controls::Forward);

		shoot = key(isPlayerTwo, Controls::Shoot);
		special = key(isPlayerTwo, Controls::Special);

		spawn = key(isPlayerTwo, Controls::Spawn);
	}
	vel = moveOffset * 5.f;
	TickData tickData;
	
	if (shoot)
	{
		tickData = this->shoot();
		//playerShootLast[i] = true;
	}
	//else
		//playerShootLast[i] = false;
	// projectiles have owners now

	//if (special)
	//	special();

	if (spawn) //Temporary and should be changed to continue.
	{
		setHealth(3);
		setHealth(3);
	}
	move();

	return tickData;
}


void Player::increasePower()
{
	if (powerLevel < 3)
		powerLevel++;
}


void Player::increaseSpecial()
{
	if (special < 3)
		special++;
}
