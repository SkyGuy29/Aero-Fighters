#include "Level.h"

Level::Level()
{
}

void Level::load(sf::Vector2u winSize, int mapId)
{
	bg.setSize(sf::Vector2f(winSize));
	bgImg.loadFromFile("Res/placeholder.jpg");
	bg.setTexture(&bgImg);
	bg.setTextureRect(sf::IntRect(0, bgDist, winSize.x, winSize.y));
	bg.setScale(1.f, -1.f);
	rect = bg.getTextureRect();
}

void Level::update(sf::Vector2u winSize)
{
	bgDist += bgSpeed;
	rect.top = bgDist;
	bg.setTextureRect(rect);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bg, states);
}
