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

void Level::update(sf::Vector2u winSize)
{
	// update player and move
	p1.update();
	p2.update();

	p1.move(sf::Vector2f(key(p1Ctrl[Right]) - key(p1Ctrl[Left]), key(p1Ctrl[Back]) - key(p1Ctrl[Forward])), winSize);
	p2.move(sf::Vector2f(key(p2Ctrl[Right]) - key(p2Ctrl[Left]), key(p2Ctrl[Back]) - key(p2Ctrl[Forward])),	winSize);

	if (key(p1Ctrl[Shoot]))
		p1.shoot(projs);
	if (key(p2Ctrl[Shoot]))
		p2.shoot(projs);

	// update projs and delete if off screen
	for (auto& proj : projs)
		proj->update(winSize);

	for (int i = projs.size() - 1; i >= 0; i--)
		if (projs[i]->shouldDelete())
		{
			delete projs[i];
			projs.erase(projs.begin() + i);
		}

	// Scrolling background
	bgDist -= bgSpeed;
	background.setTextureRect(sf::IntRect(0, bgDist, bgSize.x, bgSize.y));
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

bool Level::key(int k)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
}