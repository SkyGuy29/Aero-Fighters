#include "Level.h"

Level::Level()
{
}

void Level::load(sf::Vector2u winSize, int mapId)
{
	background.setSize(sf::Vector2f(winSize));

	p1.setPos(sf::Vector2f(winSize.x * 0.33f, winSize.y * 0.75f));
	p2.setPos(sf::Vector2f(winSize.x * 0.66f, winSize.y * 0.75f));

	bgImg.loadFromFile("Res/placeholder.jpg");
	bgDist = bgImg.getSize().y;
	background.setTextureRect(sf::IntRect(0, bgDist, winSize.x, winSize.y));
	background.setTexture(&bgImg);
}

void Level::update(sf::Vector2u winSize)
{
	// update player and move
	p1.update();
	p2.update();

	p1.move(sf::Vector2f(key(p1Ctrl[Right]) - key(p1Ctrl[Left]), key(p1Ctrl[Back]) - key(p1Ctrl[Forward])), winSize);
	p2.move(sf::Vector2f(key(p2Ctrl[Right]) - key(p2Ctrl[Left]), key(p2Ctrl[Back]) - key(p2Ctrl[Forward])),	winSize);

	if (key(p1Ctrl[Shoot]))
		p1.shoot(playerProjs);
	if (key(p2Ctrl[Shoot]))
		p2.shoot(playerProjs);

	// update projs and delete if off screen
	// Backwards loop so deleting elements doesn't mess up index numbersu
	// Deleting from the front first shifts everything after it down,
	// skipping the element after the deleted one.
	for (int i = 0; i < enemyProjs.size(); i++)
	{
		enemyProjs[enemyProjs.size() - 1 - i]->update(winSize);
		if (enemyProjs[enemyProjs.size() - 1 - i]->shouldDelete())
		{
			delete enemyProjs[enemyProjs.size() - 1 - i];
			enemyProjs.erase(enemyProjs.end() - i);
		}
	}
	for (int i = 0; i < playerProjs.size(); i++)
	{
		playerProjs[playerProjs.size() - 1 - i]->update(winSize);
		if (playerProjs[playerProjs.size() - 1 - i]->shouldDelete())
		{
			delete playerProjs[playerProjs.size() - 1 - i];
			playerProjs.erase(playerProjs.end() - i);
		}
	}


	// Scrolling background
	bgDist -= bgSpeed;
	background.setTextureRect(sf::IntRect(0, bgDist, winSize.x, winSize.y));
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);

	for (auto& enemy : enemies)
		target.draw(*enemy, states);

	target.draw(p1, states);
	target.draw(p2, states);

	for (auto& proj : enemyProjs)
		target.draw(*proj, states);
	for (auto& proj : playerProjs)
		target.draw(*proj, states);
}

bool Level::key(int k)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
}