#include "Collectable.h"


Collectable::Collectable(const short id, const sf::Vector2f position, float* newBgSpeed)
{
	backgroundSpeed = newBgSpeed;
	this->id = id;
	type = COLLECTABLE;

	// @@TODO@@
	// Avoid magic numbers; What do these mean? - Ricky
	setSize(16, 19);
	sprite.setSize(sf::Vector2f(16, 19));
	sprite.setOrigin(sprite.getSize() / 2.f);
	pos = position;
	if (id == 0)
		vel = sf::Vector2f(0, 0);
	else
		vel = sf::Vector2f(3.535f, 3.535f);
}


Collectable::Collectable(const short id, const float xPosition, const float yPosition,
	float* bgSpeed) : Collectable(id, sf::Vector2f(xPosition, yPosition), bgSpeed) {}


void Collectable::update(const sf::Vector2f winSize, std::vector<Object*>* objects,
	const bool time, int& p1Score, int& p2Score)
{
	//if (id == 0)
		//vel.y = *backgroundSpeed;

	nextFrame(8);

	if (outOfBounds(winSize) && (id == 0))
		del = true;
	//making it bounce
	else if (( outOfBounds(winSize))
			&& id != 0)
	{
		if (pos.x <= 0)
		{
			pos.x = 0;
			vel.x *= -1;
		}
		else if (pos.x >= winSize.x)
		{
			pos.x = winSize.x;
			vel.x *= -1;
		}
		if (pos.y <= 30 + view.getCenter().y - view.getSize().y / 2.f)
		{
			pos.y = 30 + view.getCenter().y - view.getSize().y / 2.f;
			vel.y *= -1;
		}
		else if (pos.y >= 240 + view.getCenter().y - view.getSize().y / 2.f)
		{
			pos.y = 240 + view.getCenter().y - view.getSize().y / 2.f;
			vel.y *= -1;
		}
	}

	//player interaction
	for (unsigned int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == PLAYER
			&& intersect(objects->at(i))
		)
			del = true;
	}

	/*if (!id && !time)
		vel.y = 0;
	else
		vel.y = 1;*/

	objectUpdate(winSize, objects);
}