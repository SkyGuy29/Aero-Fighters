#include "Entity.h"

#include <cassert>

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
	const float viewLeftBound = view->getCenter().x - view->getSize().x / 2,
		viewRightBound = view->getCenter().x + view->getSize().x/2,
		viewTopBound = view->getCenter().y - view->getSize().y/2,
		viewBottomBound = view->getCenter().y + view->getSize().y/2;
	// If on screen
	if (!(pos.x + entityData.spriteData.getBounds().width / 2.f < viewLeftBound ||              // Off the left
		pos.y + entityData.spriteData.getBounds().height / 2.f < viewTopBound ||              // Off the top
		pos.x - entityData.spriteData.getBounds().width / 2.f >= viewRightBound || // Off the right
		pos.y - entityData.spriteData.getBounds().height / 2.f >= viewBottomBound)) // Off the bottom
	{
		if ((entityFlags & 0b00000001) != 0b00000001) // If not spawned
		{
			// Set the hasSpawned flag
			entityFlags |= 0b00000001;

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

		// Maintains action of "NOTHING" if it has been 'spawned' and is still on screen.
		// ^ WHY??? they are insta deleted first tick of game LOL. Moved down to outer if - ninjune
	}
	// If not on screen and has spawned
	else if ((entityFlags & 0b00000001) == 0b00000001 && !levelEditorActive && !ignoreDeletion)
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