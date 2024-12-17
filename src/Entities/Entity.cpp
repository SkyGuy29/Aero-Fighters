#include "Entity.h"

#include <cassert>
#include <iostream>

#include "../ControllerStuff.hpp"

// Static member must be defined outside the class definition.
unsigned int Entity::next_uuid = 0;
unsigned int* Entity::currentTick;
std::unordered_map<unsigned int, sf::Sprite> Entity::spriteMap;
std::unordered_map<std::string, std::vector<ProjectilePrototype>> Entity::attackMap;
// todo: change later ??? I don't like the triple nested map
std::unordered_map<unsigned short, std::unordered_map<bool, std::unordered_map<PlayerCountry, std::string>>> Entity::playerAttackTree;
sf::View* Entity::view = nullptr;
float* Entity::backgroundSpeed = nullptr;


// spawns on the current tick.
Entity::Entity(sf::Vector2f pos, EntityID ID) :
	pos(pos), ID(ID), UUID(next_uuid++), spawnTick(*currentTick)
{
	// entities do not start with a sprite
	vel = EntityDataStorage::getData(ID).velocity;
	baseCooldown = EntityDataStorage::getData(ID).baseCooldown;
}


void Entity::setPosition(sf::Vector2f pos)
{
	this->pos = pos;
	if (sprite != nullptr)
		sprite->setPosition(pos);
}


Entity::EntityObjectAction Entity::getEntityAction(bool ignoreDeletion) noexcept
{
	const sf::Vector2f pos = getPosition();
	auto ret = EntityObjectAction::NOTHING;
	const auto& entityData = EntityDataStorage::getData(ID);
	// view: starts at 224, goes in negative direction to < -1000 
	const sf::Vector2f viewCenter = sf::Vector2f(view->getCenter().x, view->getCenter().y), viewSize = view->getSize();
	const float
		viewLeftBound = viewCenter.x - viewSize.x / 2,
		viewTopBound = viewCenter.y - viewSize.y / 2,
		viewRightBound = viewCenter.x + viewSize.x / 2,
		viewBottomBound   = viewCenter.y + viewSize.y / 2,

		entityLeftBound   = pos.x + entityData.spriteData.getBounds().width / 2.f,
		entityTopBound    = pos.y + entityData.spriteData.getBounds().height / 2.f,
		entityRightBound  = pos.x - entityData.spriteData.getBounds().width / 2.f,
		entityBottomBound = pos.y - entityData.spriteData.getBounds().height / 2.f;

	// If on screen
	if (entityLeftBound   >= viewLeftBound  && // Off the left
		entityTopBound    >= viewTopBound   && // Off the top
		entityRightBound  <= viewRightBound && // Off the right
		entityBottomBound <= viewBottomBound)  // Off the bottom
	{
		if (!spawned) // If not spawned
		{
			// Set the hasSpawned flag
			spawned = true;

			// Generate a new sprite
			spriteMap.emplace(UUID, sf::Sprite(*entityData.spriteData.getTexture()));

			// Set this entities sprite address
			sprite = &spriteMap.at(UUID);

			sprite->setPosition(pos);
			sprite->setTextureRect(entityData.spriteData.getBounds());
			sprite->setOrigin(entityData.spriteData.getBounds().width / 2, entityData.spriteData.getBounds().height / 2);

			if(vel == sf::Vector2f(0,0)) // if velocity is not already set
				vel = entityData.velocity;
		}
		// Is on screen, do not delete.
		ret = EntityObjectAction::DRAW;
	}
	// If not on screen and has spawned
	else if (spawned && !levelEditorActive && !ignoreDeletion)
		// Not on screen, please delete.
		ret = EntityObjectAction::DELETE;

	return ret;
}


void Entity::move() noexcept
{
	pos += sf::Vector2f(vel.x, vel.y);
	if (sprite != nullptr)
		sprite->setPosition(pos);
}

void Entity::setTexture(sf::Texture* texPtr)
{
	sprite->setTexture(*texPtr);
	this->frameCount = EntityDataStorage::getData(ID).spriteData.getCount();
	verticalAnimation = !EntityDataStorage::getData(ID).spriteData.isEntityAnimatedHorizontally();
	nextFrame(2);
}

/// <summary>
/// This animator allows for different frame changes.
/// </summary>
/// <param name="frameRate"></param>
void Entity::nextFrame(const int frameRate)
{
	// Increases the image rectangle by its height and loops back when 
	//it reaches the end
	currentFrame++;

	if (currentFrame >= frameCount * frameRate)
	{
		currentFrame -= frameCount * frameRate;
		animationFinished = true;
	}

	sf::Vector2i intermediary = sprite->getTextureRect().getSize();
	sf::Vector2<double> texSize   = { (double)intermediary.x, (double)intermediary.y };

	intermediary = sprite->getTextureRect().getPosition();
	sf::Vector2<double> texOffset = { (double)intermediary.x, (double)intermediary.y };

	// the dividing to an int is needed for the updates per frame delay.
	sprite->setTextureRect(sf::IntRect(
		texOffset.x + (currentFrame / frameRate) * texSize.x
		* !verticalAnimation,
		texOffset.y + (currentFrame / frameRate) * texSize.y
		* verticalAnimation,
		texSize.x, texSize.y));
}