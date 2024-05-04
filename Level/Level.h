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

#include "../ControllerStuff.hpp"


//This takes a file and interprets it to create the level.
//ALL objects in a level are held here. UIs, menus, and things that span
//through multiple levels are held by Game.

class Level : public sf::Drawable
{
public:
	Level();

	~Level();

	void load(sf::Vector2u winSize, short country, int mapId);

	void update(sf::Vector2u winSize);

private:
	void setInfScroll(bool enable);
	void updateInfScroll();

	void getInput(sf::Vector2u winSize);

	void statesUpdate(sf::Vector2u winSize);
	void japanUpdate(sf::Vector2u winSize);
	void swedenUpdate(sf::Vector2u winSize);
	void englandUpdate(sf::Vector2u winSize);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void initializeTextures(int);
	void initTexturesBoss(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);
	void initTexturesLand(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);
	void initTexturesExplosion(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);
	void initTexturesAir(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);
	void initTexturesProjectile(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);
	void initTexturesCollectable(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture* texPtr);

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
	sf::Texture roofusImg;
	sf::Texture domeAnimationImg;
	sf::Texture missileImg;
	sf::Texture avroBomberImg;
	sf::IntRect rect;
	float backgroundSpeed = 1, backgroundDist = 0, frontbackgroundDist = 0;
	short country, orient = 0;
	float backgroundSpeedup = 0.f;
	float backgroundSpeedupMax = 2.f;

	Player* p[2];

	sf::Vector2u winSize;
	bool infScrollInPos = true, infScrollEnabled = false, bossSpawned = false;
	sf::IntRect frontRect;
};