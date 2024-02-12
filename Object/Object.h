// The base class for everything that moves

#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	Object();

	virtual void update(sf::Vector2u winSize, std::vector<Object*>*);

	void rotate(float angle);

	void setRotation(float newAngle);

	void move(sf::Vector2f offset, sf::Vector2u winSize);
	void move(float offsetX, float offsetY, sf::Vector2u winSize);

	void setPos(sf::Vector2f newPos);
	void setPos(float newPosX, float newPosY);

	void setSize(sf::Vector2f newSize);
	void setSize(float newSizeX, float newSizeY);

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

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void nextFrame();

	short type, id, cooldown = 0, health;

	bool del = false;

	sf::Vector2f pos, size;
	float rot, vel;

	sf::RectangleShape sprite;

	int frameCount = 0, currentFrame = 0;

	const float PI = 3.14159f, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;
};