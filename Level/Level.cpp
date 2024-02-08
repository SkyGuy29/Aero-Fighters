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
}

void Level::update(sf::Vector2u winSize)
{
	bgDist -= bgSpeed;
	rect.top = bgDist;
	bg.setTextureRect(rect);

	//Attempt at making collectable update with level.
	c.update(winSize);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bg, states);

	//Trying to draw collectable when level draws.
	target.draw(c, states);
}
