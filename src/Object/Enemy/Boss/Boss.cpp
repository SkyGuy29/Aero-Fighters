#include "Boss.h"


Boss::Boss(const short id, const bool left, const sf::Vector2f pos,
	const sf::Vector2f vel, std::vector<Object*>* objects, const bool levelEditor) :
	Enemy(id, left, pos, vel, levelEditor)
{
	type = BOSS;

	this->startMark = startMark;
	this->backgroundDist = backgroundDist;

	if (startMark == -1)
		entered = true;

	spawnPos = pos;
	spawnVel = vel;

	switch (id)
	{
	case 0: //England Boss

	// @@TODO@@
	// Avoid magic numbers; What do these mean? - Ricky
		setSize(164, 100);
		bossPiece1 = new Boss(1, left, sf::Vector2f(pos.x - 54, pos.y + 44),
		                      vel, objects, levelEditor);
		bossPiece2 = new Boss(2, left, sf::Vector2f(pos.x, pos.y + 44), vel,
		                      objects, levelEditor);
		bossPiece3 = new Boss(3, left, sf::Vector2f(pos.x + 54, pos.y + 44),
		                      vel, objects, levelEditor);
		objects->push_back(bossPiece1);
		objects->push_back(bossPiece2);
		objects->push_back(bossPiece3);
		health = 1000;
		break;
	case 1: //England Boss Left Wing
	case 2: //England Boss Right Wing

	// @@TODO@@
	// Avoid magic numbers; What do these mean? - Ricky
		setSize(56, 60);
		health = 500;
		break;
	case 3: //England Boss Middle Part
		setSize(56, 60);
		health = 500;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Boss::update(const sf::Vector2f winSize, std::vector<Object*>* objects,
    const bool time, int& p1Score, int& p2Score)
{
	if (time == false)
		return;
	if (cooldown > 0)
		cooldown--;
	if (cooldown2 > 0)
		cooldown2--;
	if (cooldown3 > 0)
		cooldown3--;
	switch (id)
	{
	case 0: //England Boss Movement
		vel.y *= .98f; 
		bossPiece1->setPos(sf::Vector2f(pos.x - 54, pos.y + 40));
		bossPiece2->setPos(sf::Vector2f(pos.x, pos.y + 40)); 
		bossPiece3->setPos(sf::Vector2f(pos.x + 54, pos.y + 40));
		break;
	case 1: //England Boss Left Wing
		if (cooldown != 0)
			break;
		switch(pattern) //Shoots things in a cycling pattern
			{
			case 0:
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(3, 0), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-3, 0), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(0, 3), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(0, -3), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				pattern = 1;
				cooldown = 50;
				break;
			case 1:
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.707f, .707f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-0.707f, .707f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-0.707f, -0.707f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.707f, -0.707f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				pattern = 2;
				cooldown = 50;
				break;
			case 2:
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.866f, .5f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-.866f, .5f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-.866f, -.5f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.866f, -.5f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				pattern = 3;
				cooldown = 50;
				break;
			case 3:
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.966f, .259f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-.966f, .259f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(-.966f, -.259f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				objects->push_back(new Projectile(pos.x, pos.y, 
					sf::Vector2f(.966f, -.259f), sf::Vector2f(14, 14),
					ProjectileType::Breakable, false, 0, 13, 0));
				pattern = 0;
				cooldown = 200;
				break;
			}
		break;
	case 2: //England Boss Right Wing
		if (cooldown != 0)
			break;
		switch (pattern) //Shoots things in a cycling pattern
		{
		case 0:
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(3, 0), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-3, 0), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(0, 3), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(0, -3), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			pattern = 1;
			cooldown = 50;
			break;
		case 1:
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.707f, .707f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-0.707f, .707f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-0.707f, -0.707f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.707f, -0.707f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			pattern = 2;
			cooldown = 50;
			break;
		case 2:
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.866f, .5f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-.866f, .5f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-.866f, -.5f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.866f, -.5f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			pattern = 3;
			cooldown = 50;
			break;
		case 3:
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.966f, .259f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-.966f, .259f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(-.966f, -.259f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y,
				sf::Vector2f(.966f, -.259f), sf::Vector2f(14, 14),
				ProjectileType::Breakable, false, 0, 13, 0));
			pattern = 0;
			cooldown = 200;
			break;
		}
		break;
	case 3: //England Boss Middle Part
		if (cooldown == 0) //Shoots three independent patterns
		{
			objects->push_back(new Projectile(pos.x - 50, pos.y, 
				sf::Vector2f(0, 3), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 15, 0));
			objects->push_back(new Projectile(pos.x - 50, pos.y, 
				sf::Vector2f(0, 3), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 30, 15, 0));
			objects->push_back(new Projectile(pos.x - 50, pos.y, 
				sf::Vector2f(0, 3), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 45, 15, 0));
			cooldown = 300;
		}
		if (cooldown2 == 0)
		{
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(0, 5),	sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(-1.294f, 4.83f),	sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(1.294f, 4.83f), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(0, 5),	sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 25, 12, 0));
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(-1.294f, 4.83f),	sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 25, 12, 0));
			objects->push_back(new Projectile(pos.x - 30, pos.y, 
				sf::Vector2f(1.294f, 4.83f), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 25, 12, 0));
			cooldown2 = 250;
		}
		if (cooldown3 == 0)
		{
			objects->push_back(new Projectile(pos.x + 56, pos.y, 
				sf::Vector2f(1.294f, 4.83f), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x + 56, pos.y, 
				sf::Vector2f(-1.294f, 4.83f), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x - 56, pos.y, 
				sf::Vector2f(-1.294f, 4.83f),	sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			objects->push_back(new Projectile(pos.x - 56, pos.y, 
				sf::Vector2f(1.294f, 4.83f), sf::Vector2f(10, 10),
				ProjectileType::TimerPierce, false, 0, 12, 0));
			cooldown3 = 200;
		}
		break;
	}
	/// Removes the rest of the boss that would still show
	if (id == 0 && del == true)
	{
		bossPiece1->flagDelete();
		bossPiece2->flagDelete();
		bossPiece3->flagDelete();
	}
	enemyUpdate(winSize, objects, p1Score, p2Score);
}