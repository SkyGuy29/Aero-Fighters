#include "Land.h"


Land::Land(const short id, const bool left,
	float* backgroundSpeed,
	std::vector<Object*>* objects, const sf::Vector2f pos,
	const sf::Vector2f vel, const bool levelEditor
)
	: Enemy(id, left, pos, levelEditor ? sf::Vector2f(0,0) : vel, levelEditor)
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

		topPart = new Land(1, left, backgroundSpeed, objects,
		pos, vel, levelEditor); //Creates the top
		objects->push_back(topPart);
		break;
	case 0: //Weak Tank
		health = 1;
		setSpriteNum(1);
		setOrientation(7);
		break;
	case 1: //STRONG Tank
		health = 5;
		setSpriteNum(2);
		setOrientation(7);
		break;
	case 2: //fort building
		cooldown = 100;
		health = 90;
		setSize(60, 60);
		setSpriteNum(20);
		break;
	case 3: //roofus
		health = 30;
		setSize(60, 60);
		setSpriteNum(25);
		break;
	case 9: //cone
		health = 30;
		setSize(60, 60);
		setSpriteNum(24);
		break;
	case 4: //house
		health = 5;
		setSize(75, 50);
		setSpriteNum(19);
		break;
	case 5: //road gate
		health = 10;
		setSize(35, 35);
		setSpriteNum(22);
		break;
	case 6: //Hangar
		health = 30;
		setSize(80, 100);
		setSpriteNum(23);
		break;
		//SWEDEN
	case 7: //mountain base
		health = 10;
		setSize(50, 50);
		cooldown = 100;
		break;
	case 8: //landmine
		health = 3; // Moving to be a Tile Entity
		timer = 7;
		setSpriteNum(15);
		break;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Land::update(const sf::Vector2f winSize, std::vector<Object*>* objects,
    const bool time)
{
	enemyUpdate(winSize, objects);
	//Do things here only while time is moving.

	if (time != 0)
	{
		setPos(getPos().x, getPos().y + *backgroundSpeed);

		if (cooldown != 0)
			cooldown--;

		if (timer != 0)
			timer--;
		
		switch (id)
		{
		case -1: //Tank bottom
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
		case 0: case 1: //Tank top
			distance = objects->at(target)->getPos() - getPos();
			magnitude = sqrt((distance.x * distance.x) + (distance.y 
				* distance.y));
			projVelocity = sf::Vector2f(2 * distance.x / magnitude, 
				2 * distance.y / magnitude);

			angle = atan(projVelocity.y / projVelocity.x);
			angle /= PI;
			if (distance.x < 0)
				angle += 1;
			angle += .5f;
			if (angle < 0)
				angle += 2;
			angle *= 8;

			if (orientation != (int) angle && timer == 0)
			{
				timer = 15;
				if (orientation - (int)angle < 0)
					setOrientation(orientation + 1);
				else
					setOrientation(orientation - 1);
			}

			//Shoot at target player
			if (!cooldown && entered && orientation == (int) angle)
			{
				pos.y -= 0.5f;

				objects->push_back(new Projectile(getPos().x, getPos().y,
				projVelocity, sf::Vector2f(10, 10), ProjectileType::Basic, false, 0, 0, 12));

				cooldown = 100 + rand() % 50;

				target = !target;
			}
			break;
		case 2: //Building Shoot 
			if (!cooldown)
			{
				pos.y -= 0.5f;

				cooldown = 100;
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(1.84776f, 0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-1.84776f, -0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-1.84776f, 0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(1.84776f, -0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(0.76537f, 1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-0.76537f, -1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(-0.76537f, 1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
				objects->push_back(new Projectile(getPos().x, getPos().y,
				sf::Vector2f(0.76537f, -1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
				false, 0, 0, 12));
			}
			break;
		case 7: //Hangar
			if (!cooldown && entered)
			{
				cooldown = 100;
				/*objects->push_back(new Air(0, true, winSize, objects,
					pos, sf::Vector2f(0, 5)));*/
			}
			break;
		case 8: //Landmines
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