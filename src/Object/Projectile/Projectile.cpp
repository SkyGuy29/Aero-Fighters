#include "Projectile.h"


Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}


Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, ProjectileType ID, bool player, short cool, short sprit, bool fromP1)
{
	id = ID;
	setSize(size);
	tempSize = size; 
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	setSpriteNum(sprit);
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool;
	this->fromP1 = fromP1;
}


//Use when you want to delay the projectiles spawn
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, ProjectileType ID, bool player, short cool, short delay, short spriteNum, bool fromP1)
{
	this->delay = delay;
	id = ID;
	setSize(size);
	tempSize = size;
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	setSpriteNum(spriteNum);
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool;
	this->fromP1 = fromP1;
}


//The bulk of projectiles, all it does is move and check when to die.
void Projectile::update(sf::Vector2f winSize, std::vector<Object*>* objects,
	bool time, int& p1Score, int& p2Score)
{
	nextFrame(4);
	if (delay > 0) //If the delay is not up the projectile doesn't exist.
	{
		texInit = true;
		size = sf::Vector2f(0, 0);
		delay--;
		if (delay == 0)
		{
			texInit = false;
			size = tempSize;
		}
		else
			return;
	}

	if (id == 3) //Changes the size for the Japan 2 bomb
	{
		setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setOrigin(sprite.getSize() / 2.f);
	}

	if (id > 0 && cooldown > 0)
		cooldown--;

	//if (cooldown == 0 && id > 0 && id < 4 && id != 2)
	if (cooldown == 0 && (id == 3 || id == 1))
		del = true;

	if (outOfBounds(winSize))
		del = true;

	Object* closestEnemy = nullptr;
	float newEnemyDistance;
	float closestEnemyDistance = 350;

	for (unsigned int i = 0; i < objects->size(); i++)
	{
		if (type == PLAYER_PROJECTILE
			&& (id == 0 || id >= 4)
			&& ((objects->at(i)->getType() == AIR
				|| objects->at(i)->getType() == LAND
				|| objects->at(i)->getType() == BOSS)
				&& this->intersect(objects->at(i))))
		{
			//If a player projectile interacts with an enemy.
			del = true;
		}
		else if (type == ENEMY_PROJECTILE
			&& (objects->at(i)->getType() == PLAYER || (id == 6 
			&& objects->at(i)->getType() == PLAYER_PROJECTILE))
			&& this->intersect(objects->at(i)))
		{
			//If an enemy projectile interacts with something that kills it.
			if (id == 6)
				spriteNum = 14;
			else
				del = true;
		}
		if (id >= 4 && (objects->at(i)->getType() == AIR
			|| objects->at(i)->getType() == LAND)
			&& objects->at(i)->shouldDelete() == false
			&& id != 6)
		{
		//Used for tracking projectiles
			newEnemyDistance = sqrt((objects->at(i)->getPos().x - pos.x)
				* (objects->at(i)->getPos().x - pos.x) 
				+ (objects->at(i)->getPos().y - pos.y)
				* (objects->at(i)->getPos().y - pos.y));
			if (closestEnemyDistance > newEnemyDistance)
			{
				closestEnemyDistance = newEnemyDistance;
				closestEnemy = objects->at(i);
			}
		}
	}
	if (closestEnemy != nullptr)
	{
		vel = sf::Vector2f(5 * (closestEnemy->getPos().x - pos.x) / 
		closestEnemyDistance, 5 * (closestEnemy->getPos().y - pos.y) 
		/ closestEnemyDistance);
		int angle = (int)(atan(-vel.y / vel.x) / PI * 8.f); //Gets the angle and turns
		//it into one of 16 orientations.
		if (vel.x < 0) //This is to make atan have all the range.
			angle += 8;
		angle -= 4; //Offsets to match what the sprites are.
		if (angle < 0)
			angle += 16;
		if (angle > 15)
			angle -= 16;
		angle = 16 - angle; //Reverse things for more alignment.
		if (angle > 15)
			angle -= 16;
		//The math works, trust me.
		setOrientation(angle);
		sprite.setScale(1, 1); //There are only 5 sprites, so they get flipped.
		if (orientation > 8)
			sprite.setScale(sf::Vector2f(-1, 1));
		if (orientation < 12 && orientation > 4)
			sprite.setScale(sf::Vector2f(sprite.getScale().x, -1));
		texInit = false;
	}
	else if (id == 5)
	{
		float angle = atan(-vel.y / vel.x);
		if (vel.x < 0)
			angle += PI;
		angle += (PI / 6); //Consuming ten billion years in an instant.
		vel = sf::Vector2f(5 * cos(angle), -5 * sin(angle));
	}
	objectUpdate(winSize, objects);
}