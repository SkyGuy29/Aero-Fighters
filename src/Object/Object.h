#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>


/// <summary>
/// The base class for everything that moves. Making this allows us to use polymorphism
/// to handle and run through every object in the game in a little neater manner.
/// 
/// @@TODO@@
/// Split into more base classes.
/// </summary>
class Object : public sf::Drawable
{

public:
	Object();

	// 
	virtual void update(sf::Vector2f winSize, std::vector<Object*>*, bool time, int& p1Score, int& p2Score) = 0;

	static void setView(sf::View new_view);

	void objectUpdate(sf::Vector2f winSize, std::vector<Object*>*);

	virtual void move(sf::Vector2f winSize);

	void setPos(sf::Vector2f newPos);
	void setPos(float newPosX, float newPosY);

	void setSize(sf::Vector2f newSize);
	void setSize(float newSizeX, float newSizeY);

	void setVel(sf::Vector2f);
	void setVel(float, float);

	void setSpriteNum(short);
	void setTexture(sf::Texture* texPtr, sf::Vector2i size,
		sf::Vector2i offset, int frameCount, bool vertAnimation);
	// Base never used - Delete / Declare pure virtual - Ricky
	sf::Vector2f getVel() const { return vel; };

	bool outOfBounds(sf::Vector2f winSize) const;
	bool outOfTopBounds(sf::Vector2f winSize) const;
	bool outOfBottomBounds(sf::Vector2f winSize) const;

	void flagDelete() { del = true; };
	bool shouldDelete() const { return del; };

	sf::Vector2f getPos() const { return pos; };
	sf::Vector2f getSize() const { return size; };
	
	bool intersect(Object*) const;
	
	short getType() const { return type; };
	short getId() const { return id; };
	short getSpriteNum() const { return spriteNum; };

	short getOrientation() const { return orientation; };
	void setOrientation(short);

	bool isTexInit() const { return texInit; };

	enum Types
	{
		HIDDEN            =-1,
		PLAYER            = 0,
		BOSS              = 1,
		BOSS_PIECE        = 2,
		AIR               = 3,
		LAND              = 4,
		COLLECTABLE       = 5,
		PLAYER_PROJECTILE = 6,
		ENEMY_PROJECTILE  = 7,
		EXPLOSION         = 8
	};
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void nextFrame(int frameRate);

	// The type of enemy this is
	short type;
	// Entity type specific, specific enemy identifier
	short id = 0;
	// Cooldown for attacks... ? Maybe ?
	short cooldown = 0;
	// This enemies health
	short health;
	// The sprite ID this enemy uses
	short spriteNum = -1;
	short orientation = 0;
	short timer = 0;

	// In the derivations that use this, it appears that they are never actually deleted but rather just ignored, or in the case of land objects, its health is raised and the flag is removed. - ricky
	bool del = false;

	// Object Position
	sf::Vector2f pos,
		// Object size
		size,
		// Object Velocity
		vel;

	// Sprite holder for sprite objects... - Bad - ricky
	sf::RectangleShape sprite;



	// Background specific data members //

	// The speed of the backgrounds movement
	float* backgroundSpeed = nullptr;

	// The distance down the screen the background has moved, always negative, update is based upon decrementing the y position by the background movement speed.
	float* backgroundDist = nullptr;



	// Texture specific data mambers //

	short frameCount = 0, currentFrame = 0, 
		// @@TODO@@
		// Seemingly never used - Base class is never referenced, remove it. - Ricky
		image;

	sf::Vector2i texSize, texOffset;
	// @@TODO@@
	// Consider renaming some variables - ricky
	bool verticalAnimation = true, anDone = false;

	// Has the texture been initialized
	bool texInit = false;


	static sf::View view;


	// Conversion Helper Constants
	const float PI = 3.14159f, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;
};