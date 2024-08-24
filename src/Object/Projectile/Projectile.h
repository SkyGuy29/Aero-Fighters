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
	enum ProjectileType {
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
		short sprite); //Adds delay
	Projectile(float posX, float posY, sf::Vector2f vel,
		sf::Vector2f size, ProjectileType ID, bool player, short cool, short spriteNum);
	

	void update(sf::Vector2f winSize, std::vector<Object*>* objects, bool time);
private:
	short delay = 0;
	sf::Vector2f tempSize;

};