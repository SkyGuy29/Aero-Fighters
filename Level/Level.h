#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Object/Enemy/Boss/Boss.h"
#include "../Object/Enemy/Air/Air.h"
#include "../Object/Enemy/Land/Land.h"
#include "../Object/Player/Player.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"

//This takes a file and interprets it to create the level.


class Level : public sf::Drawable
{
public:
	Level();

	~Level();

	void load(sf::Vector2u winSize, short country, int mapId);

	void update(sf::Vector2u winSize);

private:
	void getInput(sf::Vector2u winSize);

	void statesUpdate(sf::Vector2u winSize);
	void japanUpdate(sf::Vector2u winSize);
	void swedenUpdate(sf::Vector2u winSize);
	void englandUpdate(sf::Vector2u winSize);

	bool key(int p, int k);

	bool button(int p, int b);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void initializeTextures(int);

	std::vector<Object*> objects;

	sf::Font font;
	sf::Text ui;

	sf::RectangleShape background, frontbackground;
	sf::Texture backgroundImg;
	sf::Texture frontbackgroundImg;
	sf::Texture playerImg;
	sf::Texture projectileImg;
	sf::Texture powerUpImg;
	sf::Texture moneyImg;
	sf::Texture explosionImg;
	sf::Texture enemyImg;
	sf::Texture enemyProjectileImg;
	sf::Texture houseImg;
	sf::Texture domeImg;
	sf::Texture gateImg;
	sf::Texture hoodImg;
	sf::Texture coneImg;
	sf::IntRect rect;
	float backgroundSpeed = 1, backgroundDist = 0, frontbackgroundDist = 0;
	short country, orient = 0;

	// Maybe put it in game or some other texture storage idk
	sf::Texture test, test2;

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
		Special,
		Spawn
	};

	enum Countries
	{
		STATES,
		JAPAN,
		SWEDEN,
		ENGLAND
	};

	int p1Ctrl[7] =
	{
		sf::Keyboard::W, // Forward
		sf::Keyboard::A, // Left
		sf::Keyboard::S, // Back
		sf::Keyboard::D, // Right
		sf::Keyboard::Q, // Shoot
		sf::Keyboard::E,  // Special
		sf::Keyboard::Space //Spawn
	};

	int p2Ctrl[7] =
	{
		sf::Keyboard::I, // Forward
		sf::Keyboard::J, // Left
		sf::Keyboard::K, // Back
		sf::Keyboard::L, // Right
		sf::Keyboard::U, // Shoot
		sf::Keyboard::O,  // Special
		sf::Keyboard::Space //Spawn
	};
};

