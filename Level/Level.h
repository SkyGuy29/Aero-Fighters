#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Object/Enemy/Enemy.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"

//This takes a file and interprets it to create the level.


class Level : public sf::Drawable
{
public:
	Level();

	void load(sf::Vector2u winSize, int mapId);

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projs;
	std::vector<Collectable*> collectables;

	sf::RectangleShape bg;
	sf::Texture bgImg;
	sf::IntRect rect;
	int bgSpeed = 1, bgDist = 0;

	//Attempt at adding collectable (Doesn't work right now)
	Collectable c = Collectable(0);
};

