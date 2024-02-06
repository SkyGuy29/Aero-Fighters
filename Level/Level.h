#pragma once

#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"

#include <vector>

class Level : public sf::Drawable
{
public:
	Level();

	void load(sf::Vector2u winSize, int mapId);

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool key(int k);

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projs;
	Player p1, p2;
	bool p2Joined = false;

	sf::Vector2u bgSize;
	sf::RectangleShape background;

	sf::Texture bgImg;

	int bgDist = 0, bgSpeed = 1;

	// TEMPORARY CONTROLS

	enum Controls
	{
		Forward,
		Left,
		Back,
		Right,
		Shoot,
		Special
	};

	int p1Ctrl[6] =
	{
		sf::Keyboard::W, // Forward
		sf::Keyboard::A, // Left
		sf::Keyboard::S, // Back
		sf::Keyboard::D, // Right
		sf::Keyboard::Q, // Shoot
		sf::Keyboard::E  // Special
	};

	int p2Ctrl[6] =
	{
		sf::Keyboard::I, // Forward
		sf::Keyboard::J, // Left
		sf::Keyboard::K, // Back
		sf::Keyboard::L, // Right
		sf::Keyboard::U, // Shoot
		sf::Keyboard::O  // Special
	};
};

