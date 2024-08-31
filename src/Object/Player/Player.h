#pragma once

#include <vector>

#include "../Projectile/Projectile.h"
#include "../Collectable/Collectable.h"
#include "../Projectile/Explosion/Explosion.h"

using ProjectileType = Projectile::ProjectileType;


class Player final : public Object
{
public:
	// Con
	Player(short country, bool playerOne, float* bgSpeed);

	void shoot(std::vector<Object*>& objects);

	void special(std::vector<Object*>& objects, sf::Vector2f winSize);

	void update(sf::Vector2f winSize, std::vector<Object*>* objects, 
		bool time) override;

	void move(sf::Vector2f winSize) override;

	bool getTime() const;
	short getHealth() const;
	short getSpecialCharge() const;

	void setHealth(short);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Projectile* movingProjectile = nullptr; //Tracks where the laser that
	//follows the player for Japan 1's bomb is.
	bool isPlayerTwo;
	short timerDeath = 0, country = -1, specialCharge = 2, powerLevel = 0,
		invincibility = 0, sideAnimation = 0, cooldownSecondary = 0,
		cooldownTime = 0;


	struct ProjectileData
	{	
		// The position offset the projectile should be placed at
		sf::Vector2f pos;

		// The Velocity the projectile should be placed with
		sf::Vector2f vel;

		// The number of this projectile to place
		unsigned char count;

		// The type of projectile to place
		ProjectileType type;

		// The projectiles cooldown
		short cooldown;

		// The sprite used for the 
		short spriteNum;
	};

};

