// The base class for everything that moves

#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	Object();

	virtual void update(sf::Vector2u winSize, std::vector<Object*>*);

	void objectUpdate(sf::Vector2u winSize, std::vector<Object*>*);

	void move(sf::Vector2u winSize);

	void setPos(sf::Vector2f newPos);
	void setPos(float newPosX, float newPosY);

	void setSize(sf::Vector2f newSize);
	void setSize(float newSizeX, float newSizeY);

	void setVel(sf::Vector2f);
	void setVel(float, float);
	sf::Vector2f getVel();

	bool outOfBounds(sf::Vector2u winSize);

	void setDelete();
	bool shouldDelete();

	sf::Vector2f getPos();
	sf::Vector2f getSize();

	void setTexture(sf::Texture* texPtr);

	// I know it's temporary
	void setRandColor();
	
	bool intersect(Object*);
	
	short getType();
	short getId();

	short getID();

	void setCountry(short c);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void nextFrame();

	short type, id, cooldown = 0, health;

	bool del = false;

	sf::Vector2f pos, size, vel;

	sf::RectangleShape sprite;

	short frameCount = 0, currentFrame = 0;

	short country = 0;

	const float PI = 3.14159f, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;

	enum Types
	{
		PLAYER = 0,
		BOSS = 1,
		BOSS_PIECE = 2,
		AIR = 3,
		LAND = 4,
		COLLECTABLE = 5,
		PLAYER_PROJECTILE = 6,
		ENEMY_PROJECTILE = 7
	};
};