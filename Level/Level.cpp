#include "Level.h"

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

	for (int i = 0; i < 2; i++)
	{
		p[i].setPos(sf::Vector2f(winSize.x * (i ? 0.75f : 0.25f), winSize.y * 0.75f));
		p[i].setRandColor();
	}
}

Player Level::getPlayer(short which)
{
	return p[which];
}

//void Level::createEnemy()
//{
//	enemies.push_back(new Enemy(0));
//
//	Enemy newEnemy = *enemies.at(enemies.size() - 1);
//
//	newEnemy.setPos(sf::Vector2f(100, 100));
//	newEnemy.setRandColor();
//}

void Level::update(sf::Vector2u winSize)
{
	bgDist -= bgSpeed;
	rect.top = bgDist;
	bg.setTextureRect(rect);

	for (int i = 0; i < 2; i++)
		p[i].update(winSize);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bg, states);
	for (int i = 0; i < 2; i++)
		target.draw(p[i]);
}
