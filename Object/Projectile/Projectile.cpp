#include "Projectile.h"

Projectile::Projectile()
{
	type = PLAYER_PROJECTILE;
}

//id 0 is basic projectiles
//id 1 is for projectiles on a timer that pierce
//id 2 is for projectiles that pierce and go off screen
//id 3 is for Japan Player 2's super
//id 4 is for tracking projectiles
//id 5 is the tracking mines of Sweden Player 2
//id 6 is for breakable projectiles
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player, short cool, short sprit)
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
}


//Use when you want to delay the projectiles spawn
Projectile::Projectile(float posX, float posY, sf::Vector2f vel,
sf::Vector2f size, short ID, bool player, short cool, short dela, short sprit)
{
	delay = dela;
	id = ID;
	setSize(size);
	tempSize = size; //Temp size holds the original size
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.f);
	setPos(posX, posY);
	this->vel = vel;
	setSpriteNum(sprit);
	if (player)
		type = PLAYER_PROJECTILE;
	else
		type = ENEMY_PROJECTILE;
	cooldown = cool + dela;
}

//The bulk of projectiles, all it does is move and check when to die.
void Projectile::update(sf::Vector2u winSize, std::vector<Object*>* objects,
bool time)
{
	nextFrame(4);
	if (delay > 0) //If the delay is not up the projectile doesn't exist.
	{
		size = sf::Vector2f(0, 0);
		delay--;
		if (delay == 0)
			size = tempSize;
	}

	if (id == 3) //Changes the size for the Japan 2 bomb
	{
		setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setSize(sf::Vector2f(size.x += 15, size.y += 15));
		sprite.setOrigin(sprite.getSize() / 2.f);
	}

	if (id > 0 && cooldown > 0)
		cooldown--;

	if (cooldown == 0 && id > 0 && id < 4 && id != 2)
		del = true;

	if (outOfBounds(winSize))
		del = true;

	Object* closestEnemy = nullptr;
	float newEnemyDistance;
	float closestEnemyDistance = 350;

	for (int i = 0; i < objects->size(); i++)
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
			&& objects->at(i)->shouldDelete() == false)
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
		int angle = atan(-vel.y / vel.x) / PI * 8; //Gets the angle and turns
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