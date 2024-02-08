#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"

class Level : public sf::Drawable
{
public:
	Level();

	void load(sf::Vector2u winSize, int mapId);
	
	//get the list of projectiles so players and enemies can create them
	Player getPlayer(short);

	void update(sf::Vector2u winSize);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Player p[2];

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projs;
	std::vector<Collectable*> collectables;

	sf::RectangleShape bg;
	sf::Texture bgImg;
	sf::IntRect rect;
	int bgSpeed = 1, bgDist = 0;
};

