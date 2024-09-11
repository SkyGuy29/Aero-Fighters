#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
/*
#include "../Object/Enemy/Boss/Boss.h"
#include "../Object/Enemy/Air/Air.h"
#include "../Object/Enemy/Land/Land.h"
#include "../Object/Player/Player.h"
#include "../Object/Projectile/Projectile.h"
#include "../Object/Collectable/Collectable.h"*/

#include "../Entities/Enemy/Air/Air_new.h"
#include "../Entities/Enemy/Land/Land_new.h"
#include "../Entities/Player/Player_new.h"
#include "../Entities/Projectile/Projectile_new.h"
#include "../Entities/PowerUp/PowerUp.h"

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
	enum Map
	{
		England,
		Israel,
		Japan,
		Meddit,
		Russia,
		States,
		Sweden,
		Space
	};

	std::vector<std::string> mapStrings = {
		"England",
		"Israel",
		"Japan",
		"Meddit",
		"Russia",
		"States",
		"Sweden",
		"Space"
	};

	Level();
	~Level();

	static void setView(sf::View new_view);

	void load(sf::Vector2f winSize, short country, Map map, bool levelEditor);
	bool update(sf::Vector2f winSize);

	void debugMode() const;

	void respawnPlayers() const;

private:
	void setInfScroll(bool enable);
	void updateInfScroll();

	void updateLevelEditor();
	void updatePlayers();

	// I feel like this is unneccessary, this should just be a switch statement in a method names "CountryUpdate" - Ricky
	void statesUpdate();
	void japanUpdate();
	void swedenUpdate();
	void englandUpdate();


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void initializeTextures(int);

	void initTexturesBoss(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesLand(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesExplosion(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesAir(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesProjectile(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);
	void initTexturesCollectable(Entity* object, sf::IntRect& objRect,
		int& frameCount, sf::Texture*& texPtr);

	// All "objects" in the game.
	// std::vector<Object*> objects;
	struct EntityHolder
	{
		// All enemy entities
		std::vector<Enemy_new*> enemies;

		// All projectile entities
		std::vector<Projectile_new*> projectiles;

		// Players
		std::vector<Player_new*> players;

		// All other entities
		std::vector<Entity*> other;

		~EntityHolder()
		{
			while (!enemies.empty())
			{
				delete enemies[enemies.size() - 1];
				enemies.pop_back();
			}

			while (!projectiles.empty())
			{
				delete projectiles[projectiles.size() - 1];
				projectiles.pop_back();
			}

			while (!players.empty())
			{
				delete players[players.size() - 1];
				players.pop_back();
			}

			while (!other.empty())
			{
				delete other[other.size() - 1];
				other.pop_back();
			}
		}
	};
	EntityHolder entities;

	sf::Font font;
	sf::Text p1Score, p2Score;
	sf::RectangleShape p1LivesRect, p2LivesRect;
	sf::Texture playerImgRepeat;

	sf::RectangleShape background, frontbackground;
	sf::Texture backgroundImg, frontbackgroundImg, playerImg, projectileImg,
		powerUpImg, moneyImg, explosionImg, enemyImg,
		enemyProjectileImg, missileImg;

	// Textures that only the map England needs
	sf::Texture houseImg, domeImg, gateImg, hoodImg,
		coneImg, roofusImg, domeAnimationImg, avroBomberImg;

	sf::IntRect rect;
	float backgroundSpeed = 1, backgroundDist = 0, frontbackgroundDist = 0;
	short country, orient = 0;
	//float backgroundSpeedup = 0.f;
	//float backgroundSpeedupMax = 2.f;
	std::vector<Player_new*>& p = entities.players;
	int player1Score = 0, player2Score = 0;

	sf::Vector2f winSize;
	bool infScrollInPos = true, infScrollEnabled = false, bossSpawned = false, levelEditor = false;
	sf::IntRect frontRect;

	bool playerShootLast[2] = { false, false };

	static sf::View view;
};