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

void Level::load(sf::Vector2u winSize, int mapId)
{
	background.setSize(sf::Vector2f(winSize));
	backgroundImg.loadFromFile("Res/placeholder.jpg");
	backgroundDist = backgroundImg.getSize().y - winSize.y;
	rect = sf::IntRect(0, backgroundDist, winSize.x, winSize.y);
	background.setTexture(&backgroundImg);
	background.setTextureRect(rect);

	
	p[0] = new Player();
	p[1] = new Player();
	objects.push_back(p[0]);
	objects.push_back(p[1]);

	// Change later. This just spaces out the players
	objects.at(0)->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	objects.at(1)->setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	test.loadFromFile("Res/AnimatorTest.png");
	objects.at(0)->setTexture(&test);
	objects.at(1)->setTexture(&test);

	objects.push_back(new Collectable(0));
	objects.back()->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.5f));

	objects.push_back(new Enemy(0));
	objects.back()->setPos(sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.25f));
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
	// 
	//Player is 0
	//Enemy is 1
	//Collectable is 2
	//Projectile is 3

	for (int i = 0; i < objects.size(); i++)
	{
		objects[objects.size() - 1 - i]->update(winSize, &objects);

		if (objects[objects.size() - 1 - i]->shouldDelete())
		{
			delete objects[objects.size() - 1 - i];
			objects.erase(objects.end() - 1 - i);
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (auto& object : objects)
		target.draw(*object);
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
		objects.at(i)->move(joy, winSize);

		if (button(i, Y))
			p[i]->shoot(objects);

		if (button(i, B))
			p[i]->special();

		// keyboard controls
		objects.at(i)->move(key(i, Right) - key(i, Left), key(i, Back) - key(i, Forward), winSize);

		if (key(i, Shoot))
			p[i]->shoot(objects);
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
