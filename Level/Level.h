#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Object/Enemy/Enemy.h"
#include "../Object/Player/Player.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"

//This takes a file and interprets it to create the level.


class Level : public sf::Drawable
{
public:
	Level();

	~Level();

	void load(sf::Vector2u winSize, int mapId);

	void update(sf::Vector2u winSize);

private:
	void getInput(sf::Vector2u winSize);

	bool key(int p, int k);

	bool button(int p, int b);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Object*> objects;

	sf::RectangleShape background;
	sf::Texture backgroundImg;
	sf::IntRect rect;
	int backgroundSpeed = 1, backgroundDist = 0;

	// Maybe put it in game or some other texture storage idk
	sf::Texture test;

	Player* p[2];

	// TEMPORARY CONTROLS

	// Controller test
	//https://hcidesign.com/gamepad/

	enum Controller
	{
		A,
		B,
		X,
		Y,
		L1,
		R1,
		L2,
		R2,
		Select,
		Start,
		L3,
		R3,
		D_Up,
		D_Down,
		D_Left,
		D_Right
	};

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

