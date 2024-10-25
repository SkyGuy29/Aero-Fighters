#include "Player_new.h"


Player_new::Player_new(sf::Vector2f pos, EntityID ID,
	int* backgroundSpeed, unsigned char orientation = 0) :
	Entity(pos, ID), IHasHealth(ID)
{

}


void Player_new::tick()
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

		if (special)
			special();

		if (spawn) //Temporary and should be changed to continue.
		{
			entities.players[0]->setHealth(3);
			entities.players[1]->setHealth(3);
		}
	}
}


void Player_new::increasePower()
{
	if (powerLevel < 3)
		powerLevel++;
	return;
}


void Player_new::increaseSpecial()
{
	if (special < 3)
		special++;
	return;
}
