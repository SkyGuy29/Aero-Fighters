#include "Level.h"

Level::Level()
{
}

Level::Level(int mapId, bool twoPlayer)
{
}

void Level::update()
{
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (auto& enemy : enemies)
		target.draw(*enemy, states);

	if (p1.isAlive())
		target.draw(p1, states);
	if (p2.isAlive())
		target.draw(p2, states);

	for (auto& proj : projs)
		target.draw(*proj, states);
}
