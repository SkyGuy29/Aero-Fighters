#include "Land_new.h"


void Land::tick(Entity::EntityHolder& entities)
{
	Enemy::tick(entities);
	//Do things here only while time is moving.

	if (time != 0)
	{
		sprite.setPosition(sprite.getPosition().x,
			sprite.getPosition().y + *backgroundSpeed
		);
		
		if (cooldown.currentCooldown != 0)
			cooldown.currentCooldown--;

		if (rotateTimer != 0)
			rotateTimer--;

		switch (ID)
		{
		case : //Tank bottom
			type = HIDDEN;
			if (topPart != nullptr)
			{
				if (topPart->shouldDelete())
				{
					topPart = nullptr;
					texInit = false;
					type = LAND;
					setSpriteNum(17);
					setOrientation(orientation % 8);
					vel = sf::Vector2f(0, 0);
				}
			}
			break;
		case EntityID::ENEMY_LAND_TANK_WEAK: case EntityID::ENEMY_LAND_TANK_STRONG: //Tank top
			sf::Vector2f distance = entities.players[target].sprite.getPosition() - sprite.getPosition();
			float magnitude = sqrt((distance.x * distance.x) + (distance.y
				* distance.y));
			sf::Vector2f projVelocity = sf::Vector2f(2 * distance.x / magnitude,
				2 * distance.y / magnitude);

			float angle = atan(projVelocity.y / projVelocity.x);
			angle /= PI;
			if (distance.x < 0)
				angle += 1;
			angle += .5f;
			if (angle < 0)
				angle += 2;
			angle *= 8;

			if (orientation != (int)angle && rotateTimer == 0)
			{
				rotateTimer = 15;
				if (orientation - (int)angle < 0)
					orientation = orientation + 1;
				else
					orientation = orientation - 1;
			}

			//Shoot at target player
			if (!cooldown.currentCooldown && entered && orientation == (int)angle)
			{
				sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 0.5f);

				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					projVelocity, sf::Vector2f(10, 10), ProjectileType::Basic, false, 0, 0, 12));

				cooldown.currentCooldown = 100 + rand() % 50;

				target = !target;
			}
			break;
		case 2: //Building Shoot 
			if (!cooldown)
			{
				pos.y -= 0.5f;

				cooldown = 100;
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(1.84776f, 0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(-1.84776f, -0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(-1.84776f, 0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(1.84776f, -0.76537f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(0.76537f, 1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(-0.76537f, -1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(-0.76537f, 1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
				entities.projectiles.push_back(new Projectile(getPos().x, getPos().y,
					sf::Vector2f(0.76537f, -1.84776f), sf::Vector2f(10, 10), ProjectileType::Basic,
					false, 0, 0, 12));
			}
			break;
		case EntityID::TILE_HANGAR_ENGLAND: //Hangar
			if (!cooldown.currentCooldown && entered)
			{
				cooldown.currentCooldown = 100;
				/*objects->push_back(new Air(0, true, winSize, objects,
					pos, sf::Vector2f(0, 5)));*/
			}
			break;
		case EntityID::LANDMINE: //Landmines
			if (!rotateTimer && orientation < 5 && del == false && entered)
			{
				orientation = orientation + 1;
				rotateTimer = 7;
			}
			if (orientation == 6)
				type = HIDDEN;
			if (del == true)
			{
				del = false;

				orientation = 6;
				health = 999;
				texInit = false;
			}
			break;
		}
	}
}