#include "Player.h"


Player::Player(sf::Vector2f pos, PlayerCountry country, bool isPlayerTwo) :
	Entity(pos, EntityID::PLAYER), IHasHealth(ID)
{

}


Entity::TickData Player::tick()
{
	// controller controls
	// works with 2 controllers

	// Move Offset
	sf::Vector2f move;

	// If the player should shoot
	bool shoot, special;
	bool spawn;

	for (int i = 0; i < 2; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			move = joystick(i);

			shoot = button(i, Controller::Y);
			special = button(i, Controller::B);

			spawn = button(i, Controller::A);
		}
		else
		{
			move.x = (float)key(i, Controls::Right) - key(i, Controls::Left);
			move.y = (float)key(i, Controls::Back) - key(i, Controls::Forward);

			shoot = key(i, Controls::Shoot);
			special = key(i, Controls::Special);

			spawn = key(i, Controls::Spawn);
		}
		vel = move * 5.f;

		/*
		if (shoot)
		{
			if (!playerShootLast[i])
				entities.players[i]->shoot(objects);
			playerShootLast[i] = true;
		}
		else
			playerShootLast[i] = false;*/
		// projectiles have owners now

		//if (special)
		//	special();

		if (spawn) //Temporary and should be changed to continue.
		{
			setHealth(3);
			setHealth(3);
		}
	}

	return TickData(NULL, (EntityDataStorage::AttackID)NULL);
}


void Player::increasePower()
{
	if (powerLevel < 3)
		powerLevel++;
	return;
}


void Player::increaseSpecial()
{
	if (special < 3)
		special++;
	return;
}
