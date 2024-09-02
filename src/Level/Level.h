#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>

#include "../Object/Enemy/Boss/Boss.h"
#include "../Object/Enemy/Air/Air.h"
#include "../Object/Enemy/Land/Land.h"
#include "../Object/Player/Player.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"

#include "../ControllerStuff.hpp"

// Renamed from TACO_BELL
#define HP_MAX SHRT_MAX


/// <summary>
/// This takes a file and interprets it to create the level.
/// ALL objects in a level are held here. UIs, menus, and things that span
/// through multiple levels are held by Game.
/// </summary>
class Level final : public sf::Drawable
{
public:
	Level();
	~Level();

	void load(sf::Vector2f winSize, short country, int mapId);
	bool update(sf::Vector2f winSize);

	void debugMode() const;

	void respawnPlayers();

private:
	void setInfScroll(bool enable);
	void updateInfScroll();

	void updatePlayers();

	// I feel like this is unneccessary, this should just be a switch statement in a method names "CountryUpdate" - Ricky
	void statesUpdate();
	void japanUpdate();
	void swedenUpdate();
	void englandUpdate();


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void initializeTextures(int);
	void initTexturesBoss(Object* object, sf::IntRect& objRect, 
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesLand(Object* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesExplosion(Object* object, sf::IntRect& objRect, 
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesAir(Object* object, sf::IntRect& objRect, 
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesProjectile(Object* object, sf::IntRect& objRect, 
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesCollectable(Object* object, sf::IntRect& objRect, 
		int& frameCount, sf::Texture*& texPtr);

	// All "objects" in the game.
	std::vector<Object*> objects;

	sf::Font font;
	sf::Text ui;

	sf::RectangleShape background, frontbackground;
	sf::Texture backgroundImg, frontbackgroundImg, playerImg, projectileImg,
		powerUpImg, moneyImg, explosionImg, enemyImg,
		enemyProjectileImg, houseImg, domeImg, gateImg, hoodImg,
		coneImg, roofusImg, domeAnimationImg, missileImg, avroBomberImg;
	sf::IntRect rect;
	float backgroundSpeed = 1, backgroundDist = 0, frontbackgroundDist = 0;
	short country, orient = 0;
	//float backgroundSpeedup = 0.f;
	//float backgroundSpeedupMax = 2.f;

	Player* p[2];

	sf::Vector2f winSize;
	bool infScrollInPos = true, infScrollEnabled = false, bossSpawned = false;
	sf::IntRect frontRect;

	bool playerShootLast[2] = { false, false };
};