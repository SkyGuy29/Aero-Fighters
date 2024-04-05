#include "Level.h"
#include <fstream>
#include <string>

Level::Level()
{
	font.loadFromFile("res/aero-fighters.ttf");
}

Level::~Level()
{
	while (objects.size() > 0)
	{
		delete objects[objects.size() - 1];
		objects.erase(objects.end() - 1);
	}
}

void Level::load(sf::Vector2u winSize, short country, int mapId)
{
	this->country = country;

	ui.setFont(font);
	ui.setPosition(0, 0);

	switch (country)
	{
	case STATES:
		backgroundImg.loadFromFile("Res/States/States.png");
		break;
	case JAPAN:
		backgroundImg.loadFromFile("Res/Japan/Japan.png");
		break;
	case SWEDEN:
		backgroundImg.loadFromFile("Res/Sweden/Sweden.png");
		break;
	case ENGLAND:
		backgroundImg.loadFromFile("Res/England/England.png");
	}

	background.setSize(sf::Vector2f(winSize));
	backgroundDist = backgroundImg.getSize().y - winSize.y;
	rect = sf::IntRect(0, backgroundDist, winSize.x, winSize.y);
	background.setTexture(&backgroundImg);
	background.setTextureRect(rect);

	playerImg.loadFromFile("Res/Misc/players.png");
	projectileImg.loadFromFile("Res/Misc/Projectiles.png");
	powerUpImg.loadFromFile("Res/Misc/Powerups.png");
	moneyImg.loadFromFile("Res/Misc/money.png");
	explosionImg.loadFromFile("Res/Misc/Explosion.png");

	p[0] = new Player(country, true);
	p[1] = new Player(country, false);
	objects.push_back(p[0]);
	objects.push_back(p[1]);

	// Change later. This just spaces out the players
	objects.at(0)->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	objects.at(1)->setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	objects.at(0)->setTexture(&playerImg, sf::Vector2i(32, 32), sf::Vector2i(0, 16), 5, false);
	objects.at(1)->setTexture(&playerImg, sf::Vector2i(32, 32), sf::Vector2i(0, 16), 5, false);

	objects.push_back(new Collectable(0, sf::Vector2f(winSize.x / 2, winSize.y / 2)));

	//land enemy
	/*sf::Vector2f pos = sf::Vector2f(winSize.x * 0.5, winSize.y * 0.1);
	sf::Vector2f vel = sf::Vector2f(0, 0);
	objects.push_back(new Land(0, true, &backgroundSpeed, winSize, &objects, pos, vel));*/

	short type, id;
	sf::Vector2f pos, vel;

	std::fstream file;

	switch (country)
	{
	case STATES:
		break;
	case JAPAN:
		break;
	case SWEDEN:
		break;
	case ENGLAND:
		file.open("Res/England/enemies.txt");
	}

	while (file.is_open() && !file.eof())
	{
		file >> type;
		file >> id;
		file >> pos.x;
		file >> pos.y;
		file >> vel.x;
		file >> vel.y;
		

		switch (type)
		{
		case 0: //land
			objects.push_back(new Land(id, true, &backgroundSpeed, winSize, &objects, pos, vel));
			break;
		case 1: //air
			objects.push_back(new Air(id, true, winSize, &objects, pos, vel));
			break;
		}
	}
}

void Level::update(sf::Vector2u winSize)
{
	//How do I draw text?
	std::string s = "P1 Lives: ";
	s += p[0]->getHealth();
	s += "  P2 Lives: ";
	s += p[1]->getHealth();
	s += "  P1 Bombs: ";
	s += p[0]->getSpecialCharge();
	s += "  P2 Bombs: ";
	s += p[1]->getSpecialCharge();
	s += "  Score: 0";
	s += "";
	ui.setString(s);
	// The background has to scroll backwards to get the effect that we want.
	backgroundDist -= backgroundSpeed;
	rect.top = backgroundDist;
	background.setTextureRect(rect);
	// for smoothing out background. 
	// I offset the the background by negative decapitating the background float. 
	// SFML will smooth out not pixel aligned things.
	background.setPosition(0, float(int(backgroundDist) - backgroundDist));
	
	getInput(winSize);

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop index
	// delete first, then erase

	//polymorphism -- All objects are stored in this vector, they can be
	//identified using getType()
	short moneyOffset = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[objects.size() - 1 - i]->isTexInit())
			switch (objects[objects.size() - 1 - i]->getType())
			{
			case Object::EXPLOSION:
				switch (objects[objects.size() - 1 - i]->getSpriteNum())
				{
				case 0:
					objects[objects.size() - 1 - i]->setTexture(&explosionImg,
					sf::Vector2i(48, 48), sf::Vector2i(0, 0), 16, false);
					break;
				case 1:
					objects[objects.size() - 1 - i]->setTexture(&explosionImg,
					sf::Vector2i(47, 37), sf::Vector2i(0, 49), 11, false);
					break;
				case 2:
					objects[objects.size() - 1 - i]->setTexture(&explosionImg,
					sf::Vector2i(78, 80), sf::Vector2i(0, 87), 14, false);
					break;
				case 3:
					objects[objects.size() - 1 - i]->setTexture(&explosionImg,
					sf::Vector2i(38, 41), sf::Vector2i(0, 168), 12, false);
					break;
				}
				break;
			case Object::PLAYER_PROJECTILE: case Object::ENEMY_PROJECTILE:
				switch (objects[objects.size() - 1 - i]->getSpriteNum())
				{
				case 0: 
					objects[objects.size() - 1 - i]->setTexture(&projectileImg, 
					sf::Vector2i(11, 18), sf::Vector2i(0, 0), 3, false);
					break;
				case 1:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(16, 30), sf::Vector2i(0, 19), 3, false);
					break;
				case 2:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(31, 30), sf::Vector2i(0, 50), 3, false);
					break;
				case 3:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(47, 46), sf::Vector2i(0, 81), 3, false);
					break;
				case 4:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(9, 28), sf::Vector2i(0, 128), 3, false);
					break;
				case 5:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(16, 32), sf::Vector2i(0, 157), 3, false);
					break;
				case 6:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(41, 44), sf::Vector2i(0, 190), 3, false);
					break;
				case 7:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(64, 48), sf::Vector2i(0, 235), 3, false);
					break;
				case 8:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(15, 29), sf::Vector2i(0, 284), 3, false);
					break;
				case 9:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(9, 31), sf::Vector2i(0, 314), 1, false);
					break;
				case 10:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(9, 31), sf::Vector2i(0, 346), 3, false);
					break;
				case 11:
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(16, 31), sf::Vector2i(0, 378), 3, false);
					break;
				case 12: //Enemy Projectile 1
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(11, 18), sf::Vector2i(0, 0), 3, false);
					break;
				case 13: //Enemy Projectile 2
					objects[objects.size() - 1 - i]->setTexture(&projectileImg,
					sf::Vector2i(11, 18), sf::Vector2i(0, 0), 3, false);
					break;
				}
				break;
			case Object::COLLECTABLE:
				switch (objects[objects.size() - 1 - i]->getID())
				{
				case 0:
					switch (country)
					{
					case 0:
						moneyOffset = 22;
						break;
					case 1:
						moneyOffset = 0;
						break;
					case 2:
						moneyOffset = 66;
						break;
					case 3:
						moneyOffset = 44;
						break;
					}
					objects[objects.size() - 1 - i]->setTexture(&moneyImg,
					sf::Vector2i(11, 12), sf::Vector2i(moneyOffset, 0), 2, false);
					break;
				case 1:
					objects[objects.size() - 1 - i]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 20), 8, false);
					break;
				case 2:
					objects[objects.size() - 1 - i]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 0), 8, false);
					break;
				case 3:
					objects[objects.size() - 1 - i]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 40), 8, false);
					break;
				}
			}
		objects[objects.size() - 1 - i]->update(winSize, &objects, p[1]->getTime());
	}

	for (int i = 0; i < objects.size(); i++)
		if (objects[objects.size() - 1 - i]->shouldDelete())
		{
			delete objects[objects.size() - 1 - i];
			objects.erase(objects.end() - 1 - i);
		}

	//Random events!!!

	//Fly straight in formation
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, winSize.y * -0.25f);
		sf::Vector2f vel = sf::Vector2f(0, 4);

		for (int i = 0; i < 6; i++)
		{
			switch (i)
			{
			case 0:
				break;
			case 1:
				pos += sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y);
				break;
			case 2:
			case 4:
			case 5:
				pos += sf::Vector2f(0.1f * winSize.y, 0);
				break;
			case 3:
				pos += sf::Vector2f(-0.15f * winSize.y, -0.1f * winSize.y);
			}

			objects.push_back(new Air(0, true, winSize, &objects, pos, vel));
		}
	}
	//Turn left
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, 
			winSize.y * -0.25f);
		sf::Vector2f vel = sf::Vector2f(0, 4);
		objects.push_back(new Air(1, true, winSize, &objects, pos, vel));
	}
	//Turn Right
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x,
			winSize.y * -0.25f);
		sf::Vector2f vel = sf::Vector2f(0, 4);
		objects.push_back(new Air(1, true, winSize, &objects, pos, vel));
	}
	//Flipping planes
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x,
			winSize.y * -0.25f);
		sf::Vector2f vel = sf::Vector2f(1, 7);

		objects.push_back(new Air(2, true, winSize, &objects, pos, vel));

		for (int i = 0; i < 3; i++)
		{
			pos += sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y);
			objects.push_back(new Air(2, true, winSize, &objects, pos, vel));
		}
	}
	//Mini choppers left
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f(0, 0.15 * winSize.y);
		sf::Vector2f vel = sf::Vector2f(4, 0);
		objects.push_back(new Air(3, true, winSize, &objects, pos, vel));
	}
	//Mini choppers right
	if (rand() % 200 == -1)
	{
		sf::Vector2f pos = sf::Vector2f(winSize.x, 0.15 * winSize.y);
		sf::Vector2f vel = sf::Vector2f(-4, 0);
		objects.push_back(new Air(3, false, winSize, &objects, pos, vel));
	}

	switch (country)
	{
	case STATES:
		statesUpdate(winSize);
		break;
	case JAPAN:
		japanUpdate(winSize);
		break;
	case SWEDEN:
		swedenUpdate(winSize);
		break;
	case ENGLAND:
		englandUpdate(winSize);
	}
}

void Level::statesUpdate(sf::Vector2u winSize)
{
	if (backgroundDist <= 0)
		backgroundSpeed = 0;
	return;
}

void Level::japanUpdate(sf::Vector2u winSize)
{
	if (backgroundDist <= 0 || !(p[1]->getTime()))
		backgroundSpeed = 0;
	else
		backgroundSpeed = 1;
	return;
}

void Level::swedenUpdate(sf::Vector2u winSize)
{
	if (backgroundDist <= 0)
		backgroundSpeed = 0;
	return;
}

void Level::englandUpdate(sf::Vector2u winSize)
{
	if (backgroundDist <= 0)
		backgroundSpeed = 0;
	//Slow down for fort
	else if (backgroundDist <= 1405 && backgroundDist > 1264)
		backgroundSpeed = 0.5;
	else
		backgroundSpeed = 1;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (int i = objects.size() - 1; i >= 0; i--)
		target.draw(*objects[i]);
}

void Level::getInput(sf::Vector2u winSize)
{
	// controller controls
	// works with 2 controllers
	sf::Vector2f joy;

	for (int i = 0; i < 2; i++)
	{
		joy.x = sf::Joystick::getAxisPosition(i, sf::Joystick::X) / 100.f;
		joy.y = sf::Joystick::getAxisPosition(i, sf::Joystick::Y) / 100.f;

		// fix drift under 15%
		joy.x *= std::abs(joy.x) > 0.15f;
		joy.y *= std::abs(joy.y) > 0.15f;
		objects.at(i)->setVel(joy);

		if (button(i, Y))
			p[i]->shoot(objects);

		if (button(i, B))
			p[i]->special(objects, winSize);

		// keyboard controls
		objects.at(i)->setVel((key(i, Right) - key(i, Left)) * 5,
		(key(i, Back) - key(i, Forward)) * 5);

		if (key(i, Shoot))
			p[i]->shoot(objects);

		if (key(i, Special))
			p[i]->special(objects, winSize);

		if (key(i, Spawn)) //Temporary and should be changed to continue.
		{
			p[0]->setHealth(3);
			p[1]->setHealth(3);
		}
	}
}


// These two are for shortening code
bool Level::key(int p, int k)
{
	if (p)
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p2Ctrl[k]));
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p1Ctrl[k]));
}

bool Level::button(int p, int b)
{
	return sf::Joystick::isButtonPressed(p, b);
}
