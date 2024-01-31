#include "Level.h"

Level::Level()
{
}

Level::Level(int mapId)
{
}

void Level::update()
{
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
