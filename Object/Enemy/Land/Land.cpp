#include "Land.h"

Land::Land(short id, bool left, float* backgroundSpeed, sf::Vector2u winSize, std::vector<Object*>* objects,
	sf::Vector2f pos, sf::Vector2f vel) : Enemy(id, left, pos, vel)
{
	type = LAND;

	this->backgroundSpeed = backgroundSpeed;
	target = rand() % 2;

	//All regular enemies are 32 x 32
	setSize(32, 32);

	switch (id)
	{
		//ENGLAND
	case 0: //Weak Tank
		health = 1;
		setSpriteNum(1);
		break;
	case 1: //STRONG Tank
		health = 5;
		setSpriteNum(2);
		break;
	case 2: //fort building
		health = 60;
		setSize(60, 60);
		break;
	case 3: //smaller fort buildings
		health = 15;
		setSize(60, 60);
		break;
	case 4: //house
		health = 5;
		setSize(75, 50);
		break;
	case 5: //road gate
		health = 10;
		setSize(35, 35);
		break;
	case 6: //Hangar
		health = 30;
		setSize(80, 100);
		break;
		//SWEDEN
	case 7: //mountain base
		health = 10;
		setSize(50, 50);
		break;
	case 8: //landmine
		health = 1;
		setSpriteNum(16);
		break;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
	//setRandColor();
}

void Land::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	enemyUpdate(winSize, objects);

	//Do things here only while time is moving.
	if (time)
	{
		setPos(getPos().x, getPos().y + *backgroundSpeed);

		if (cooldown)
			cooldown--;

		switch (id)
		{
		case 0:
			break;
		case 1:
			//Shoot at target player
			if (cooldown == 0 && entered)
			{
				sf::Vector2f distance = objects->at(target)->getPos() - getPos();
				float magnitude = sqrt((distance.x * distance.x) + (distance.y * distance.y));
				sf::Vector2f projVelocity = sf::Vector2f(2 * distance.x / magnitude, 2 * distance.y / magnitude);

				objects->push_back(new Projectile(getPos().x, getPos().y,
					projVelocity, sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				cooldown = 100 + rand() % 50;

				if (target == 0)
					target = 1;
				else
					target = 0;
			}
		}
	}
}