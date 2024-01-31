#pragma once

#include "Player.h"
#include "Enemy.h"

#include <vector>

class Level : public sf::Drawable
{
public:
	Level();
	Level(int mapId, bool twoPlayer);

	void update();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projs;
	Player p1 = Player(), p2;

	sf::RectangleShape background;
	sf::Texture backgroundImg;
};

