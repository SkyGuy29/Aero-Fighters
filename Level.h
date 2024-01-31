#pragma once

#include "Player.h"
#include "Enemy.h"

#include <vector>

class Level : public sf::Drawable
{
public:
	Level();
	Level(int mapId);

	void update();

	void movePlayers(sf::Vector2f p1Pos, sf::Vector2f p2Pos, sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projs;
	Player p1, p2;
	bool p2Joined = false;

	sf::RectangleShape background;
	sf::Texture backgroundImg;
};

