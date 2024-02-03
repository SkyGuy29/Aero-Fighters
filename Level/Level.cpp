#include "Level.h"

Level::Level()
{
}

void Level::load(sf::Vector2u winSize, int mapId)
{
	bgSize = winSize;
	background.setSize(sf::Vector2f(bgSize));

	p1.setPos(sf::Vector2f(bgSize.x * 0.33f, bgSize.y * 0.75f));
	p2.setPos(sf::Vector2f(bgSize.x * 0.66f, bgSize.y * 0.75f));

	bgImg.loadFromFile("Res/placeholder.jpg");
	bgDist = bgImg.getSize().y;
	background.setTextureRect(sf::IntRect(0, bgDist, bgSize.x, bgSize.y));
	background.setTexture(&bgImg);
}

void Level::update()
{
	background.setTextureRect(sf::IntRect(0, --bgDist, bgSize.x, bgSize.y));
}

void Level::movePlayers(sf::Vector2f p1Pos, sf::Vector2f p2Pos, sf::Vector2u winSize)
{
	if (p1.isAlive())
		p1.move(p1Pos, winSize);
	if (p2.isAlive())
		p2.move(p2Pos, winSize);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (auto& enemy : enemies)
		target.draw(*enemy, states);

	target.draw(p1, states);
	target.draw(p2, states);

	for (auto& proj : projs)
		target.draw(*proj, states);
}
