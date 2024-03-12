#include "Level.h"

Level::Level()
{
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

	switch (country)
	{
	case SWEDEN:
		backgroundImg.loadFromFile("Res/Sweden/Sweden.png");
		break;
	default:
		backgroundImg.loadFromFile("Res/placeholder.png");
	}

	background.setSize(sf::Vector2f(winSize));
	backgroundDist = backgroundImg.getSize().y - winSize.y;
	rect = sf::IntRect(0, backgroundDist, winSize.x, winSize.y);
	background.setTexture(&backgroundImg);
	background.setTextureRect(rect);

	playerImg.loadFromFile("Res/Misc/players.png");

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

	objects.push_back(new Collectable(1));
	objects.back()->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.5f));

	sf::Vector2f pos = sf::Vector2f(winSize.x * 0.5, winSize.y * 0.1);
	sf::Vector2f vel = sf::Vector2f(0, 0);
	objects.push_back(new Land(0, true, &backgroundSpeed, winSize, &objects, pos, vel));
}

void Level::update(sf::Vector2u winSize)
{
	// The background has to scroll backwards to get the effect that we want.
	backgroundDist -= backgroundSpeed;
	rect.top = backgroundDist;
	background.setTextureRect(rect);
	
	getInput(winSize);

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop index
	// delete first, then erase

	//polymorphism -- All objects are stored in this vector, they can be
	//identified using getType()
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[objects.size() - 1 - i]->isTexInit())
			switch (objects[objects.size() - 1 - i]->getType())
			{
			case Object::EXPLOSION:
				objects[objects.size() - 1 - i]->setTexture(&playerImg, sf::Vector2i(32, 32), sf::Vector2i(0, 16), 5, false);
				break;
			case Object::PLAYER_PROJECTILE: case Object::ENEMY_PROJECTILE:
				objects[objects.size() - 1 - i]->setTexture(&playerImg, sf::Vector2i(objects[objects.size() - 1 - i]->getSize().x, objects[objects.size() - 1 - i]->getSize().y), sf::Vector2i(0, 16), 1, false);
				break;
			}
		objects[objects.size() - 1 - i]->update(winSize, &objects);
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

	if (backgroundDist <= 0)
		backgroundSpeed = 0;
}

void Level::statesUpdate(sf::Vector2u winSize)
{
	return;
}

void Level::japanUpdate(sf::Vector2u winSize)
{
	return;
}

void Level::swedenUpdate(sf::Vector2u winSize)
{
	return;
}

void Level::englandUpdate(sf::Vector2u winSize)
{
	return;
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
