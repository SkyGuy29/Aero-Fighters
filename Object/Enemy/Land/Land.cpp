#include "Land.h"

Land::Land(short id, bool left, float* backgroundSpeed, sf::Vector2u winSize, std::vector<Object*>* objects,
	sf::Vector2f pos, sf::Vector2f vel) : Enemy(id, left, pos, vel)
{
	type = LAND;

	this->backgroundSpeed = backgroundSpeed;
	target = rand() % 2;

	//All regular enemies are 32 x 32
	setSize(32, 32);
	setOrientation(0);

	switch (id)
	{
		//ENGLAND
	case -1: //Tank Bottom
		health = 99;
		setSpriteNum(0);

		angle = atan(vel.y / vel.x);
		angle /= PI;
		if (vel.x < 0)
			angle += 1;
		angle += .5;
		if (angle < 0)
			angle += 2;
		angle *= 8;

		setOrientation((int)angle);

		topPart = new Land(1, left, backgroundSpeed, winSize, objects,
		pos, vel); //Creates the top
		objects->push_back(topPart);
		break;
	case 0: //Weak Tank
		health = 1;
		setSpriteNum(2);
		setOrientation(7);
		break;
	case 1: //STRONG Tank
		health = 5;
		setSpriteNum(2);
		setOrientation(7);
		break;
	case 2: //fort building
		cooldown = 100;
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
		health = 3;
		timer = 7;
		setSpriteNum(15);
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

		if (timer)
			timer--;

		
		switch (id)
		{
		case -1:
			type = HIDDEN;
			if (topPart != nullptr)
			{
				if (topPart->shouldDelete())
				{
					topPart = nullptr;
					texInit = false;
					type = LAND;
					setSpriteNum(17);
					setOrientation(orientation % 8);
					vel = sf::Vector2f(0, 0);
				}
			}
			break;
		case 0: case 1:
			distance = objects->at(target)->getPos() - getPos();
			magnitude = sqrt((distance.x * distance.x) + (distance.y * distance.y));
			projVelocity = sf::Vector2f(2 * distance.x / magnitude, 2 * distance.y / magnitude);

			angle = atan(projVelocity.y / projVelocity.x);
			angle /= PI;
			if (distance.x < 0)
				angle += 1;
			angle += .5;
			if (angle < 0)
				angle += 2;
			angle *= 8;

			if (orientation != (int) angle && !timer)
			{
				timer = 15;
				if (orientation - (int)angle < 0)
					setOrientation(orientation + 1);
				else
					setOrientation(orientation - 1);
			}

			//Shoot at target player
			if (cooldown == 0 && entered && orientation == (int) angle)
			{

				objects->push_back(new Projectile(getPos().x, getPos().y,
				projVelocity, sf::Vector2f(10, 10), 0, false, 0, 0, 12));

				cooldown = 100 + rand() % 50;

				if (target == 0)
					target = 1;
				else
					target = 0;
			}
			break;
		case 2:
			if (!cooldown)
			{
				cooldown = 100;
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(1.84776, 0.76537), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-1.84776, -0.76537), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-1.84776, 0.76537), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(1.84776, -0.76537), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(0.76537, 1.84776), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-0.76537, -1.84776), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-0.76537, 1.84776), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(0.76537, -1.84776), sf::Vector2f(10, 10), 0, false, 0, 0, 12));
			}
			break;
		case 7:
			if (!cooldown)
			{
				cooldown = 60;
				//Create a plane
			}
			break;
		case 8:
			if (!timer && orientation < 5 && del == false && entered)
			{
				setOrientation(orientation + 1);
				timer = 7;
			}
			if (orientation == 6)
				type = HIDDEN;
			if (del == true)
			{
				del = false;
				setOrientation(6);
				health = 999;
				texInit = false;
			}
			break;
		}
	}
}