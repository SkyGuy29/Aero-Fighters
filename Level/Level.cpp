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

	p[0].setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	p[1].setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));
}

void Level::update(sf::Vector2u winSize)
{
	bgDist -= bgSpeed;
	rect.top = bgDist;
	bg.setTextureRect(rect);
	c.update(winSize);

}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bg, states);
	for (auto& proj : playerProjs)
		target.draw(*proj);
	for (auto& proj : enemyProjs)
		target.draw(*proj);
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
			p[i].shoot(playerProjs);

		if (button(i, B))
			p[i].special();

		// keyboard controls
		p[i].move(key(i, Right) - key(i, Left), key(i, Back) - key(i, Forward), winSize);

		if (key(i, Shoot))
			p[i].shoot(playerProjs);
	}
}

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
