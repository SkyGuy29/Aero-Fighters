// The base class for everything that moves. Making this allows us to use polymorphism
// to handle and run through every object in the game in a little neater manner.

#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	Object();

	virtual void update(sf::Vector2u winSize, std::vector<Object*>*, bool time);

	void objectUpdate(sf::Vector2u winSize, std::vector<Object*>*);

	virtual void move(sf::Vector2u winSize);

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


	void setTexture(sf::Texture* texPtr, sf::Vector2i size, 
	sf::Vector2i offset, int frameCount, bool vertAnimation);
	
	bool intersect(Object*);
	
	short getType();
	short getID();

	short getSpriteNum();
	void setSpriteNum(short);

	short getOrientation();
	void setOrientation(short);

	bool isTexInit();

	enum Types
	{
		HIDDEN = -1,
		PLAYER = 0,
		BOSS = 1,
		BOSS_PIECE = 2,
		AIR = 3,
		LAND = 4,
		COLLECTABLE = 5,
		PLAYER_PROJECTILE = 6,
		ENEMY_PROJECTILE = 7,
		EXPLOSION = 8
	};

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void nextFrame(int frameRate);

	short type, id = 0, cooldown = 0, health, spriteNum = -1, orientation = 0, 
	timer = 0;

	bool del = false;
	bool texInit = false;

	sf::Vector2f pos, size, vel;

	sf::RectangleShape sprite;

	float* backgroundSpeed = nullptr;
	float* backgroundDist = nullptr;

	short frameCount = 0, currentFrame = 0, image;
	sf::Vector2i texSize, texOffset;
	bool verticalAnimation = true, anDone = false;

	const float PI = 3.14159f, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;
};