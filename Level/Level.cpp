#include "Level.h"
#include "../Object/Collectable/Collectable.h"

Level::Level()
{
}

void Level::load(sf::Vector2u winSize, int mapId)
{
	bg.setSize(sf::Vector2f(winSize));
	bgImg.loadFromFile("Res/placeholder.jpg");
	bgDist = bgImg.getSize().y - winSize.y;
	rect = sf::IntRect(0, bgDist, winSize.x, winSize.y);
	bg.setTexture(&bgImg);
	bg.setTextureRect(rect);

	// Change later. This just spaces out the players
	p[0].setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	p[1].setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	test.loadFromFile("Res/AnimatorTest.png");
	p[0].setTexture(&test);
	p[1].setTexture(&test);

	objects.push_back(new Collectable(0));

	objects.push_back(new Enemy(0));
	objects.back()->setPos(sf::Vector2f(winSize.x * 0.5f, winSize.y * 0.25f));
}

void Level::update(sf::Vector2u winSize)
{
	// The background has to scroll backwards to get the effect that we want.
	bgDist -= bgSpeed;
	rect.top = bgDist;
	bg.setTextureRect(rect);
	
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

	for (int i = 0; i < 2; i++)
		p[i].update(winSize, &objects);

	//Goes through all objects and checks if they intersect
	for (int originalObject = 0; originalObject < objects.size(); originalObject++)
	{
		for (int otherObject = 0; otherObject < objects.size(); otherObject++)
		{
			if (originalObject != otherObject)
			{
				objects[originalObject]->intersect(objects[otherObject]);
			}
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bg, states);

	for (auto& object : objects)
		target.draw(*object);

	for (int i = 0; i < 2; i++)
		target.draw(p[i]);
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
		p[i].move(joy, winSize);

		if (button(i, Y))
			p[i].shoot(objects);

		if (button(i, B))
			p[i].special();

		// keyboard controls
		p[i].move(key(i, Right) - key(i, Left), key(i, Back) - key(i, Forward), winSize);

		if (key(i, Shoot))
			p[i].shoot(objects);
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
