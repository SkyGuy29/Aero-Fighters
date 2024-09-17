#pragma once

#include "../Object.h"
#include <iostream>

class Projectile : public Object
{
public:
	//id 0 is basic projectiles
	//id 1 is for projectiles on a timer that pierce
	//id 2 is for projectiles that pierce and go off screen
	//id 3 is for Japan Player 2's super
	//id 4 is for tracking projectiles
	//id 5 is the tracking mines of Sweden Player 2
	//id 6 is for breakable projectiles
	enum ProjectileType : unsigned char {
		Basic,
		TimerPierce,
		PierceOffscreen,
		JapanPlayer2Super,
		Tracking,
		SwedenPlayer2Mine,
		Breakable
	};

	Projectile();
	Projectile(float posX, float posY, sf::Vector2f vel,
		sf::Vector2f size, ProjectileType ID, bool player, short cool, short delay,
		short sprite, bool fromP1); //Adds delay
	Projectile(float posX, float posY, sf::Vector2f vel,
		sf::Vector2f size, ProjectileType ID, bool player, short cool, short spriteNum, bool fromP1);

	void update(sf::Vector2f winSize, std::vector<Object*>* objects, bool time, int& p1Score, int& p2Score);

	bool isFromP1() const { return fromP1; }
private:
	bool fromP1 = false;
	short delay = 0;
	sf::Vector2f tempSize;

};