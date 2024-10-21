#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>

#include "../Utility/EntityData/EntityManagementInterface.h"
#include "../ControllerStuff.hpp"

// Renamed from TACO_BELL
#define HP_MAX SHRT_MAX


/// <summary>
/// This takes a file and interprets it to create the level.
/// ALL objects in a level are held here. UIs, menus, and things that span
/// through multiple levels are held by Game.
/// </summary>
class Level final
{
public:
	

	Level(sf::RenderWindow& window);
	~Level();

	static void setView(sf::View new_view);

	float getBackgroundSpeed();

	void load(sf::Vector2f winSize, short country, Map map, bool levelEditor);
	bool update(sf::Vector2f winSize);

	void debugMode() const;
	int skipToBoss();

	void respawnPlayers() const;
private:

	void updateLevelEditor();

	// I feel like this is unneccessary, this should just be a switch statement in a method names "CountryUpdate" - Ricky
	void statesUpdate();
	void japanUpdate();
	void swedenUpdate();
	void englandUpdate();

	sf::Font font;
	sf::Text p1Score, p2Score;
	sf::RectangleShape p1LivesRect, p2LivesRect;
	sf::Texture playerImgRepeat;

	sf::RectangleShape background, bossBackground;
	sf::Texture backgroundImg, bossBackgroundImg, playerImg, projectileImg,
		powerUpImg, moneyImg, explosionImg, enemyImg,
		enemyProjectileImg, missileImg;

	// Textures that only the map England needs
	sf::Texture houseImg, domeImg, gateImg, hoodImg,
		coneImg, roofusImg, domeAnimationImg, avroBomberImg;

	sf::RenderWindow& window;

	sf::IntRect rect;
	float backgroundSpeed = 1, backgroundDist = 0;
	short country, orient = 0;
	//float backgroundSpeedup = 0.f;
	//float backgroundSpeedupMax = 2.f;
	int player1Score = 0, player2Score = 0;
	unsigned int currentTick = 0;

	sf::Vector2f winSize;
	bool bossSpawned = false, levelEditor = false, bossBackgroundSet = false;

	bool playerShootLast[2] = { false, false };

	static sf::View view;
};