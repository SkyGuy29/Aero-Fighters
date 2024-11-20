#include "Entity.h"

#include "../ControllerStuff.hpp"

// Static member must be defined outside the class definition.
unsigned int Entity::next_uuid = 0;
unsigned int* Entity::currentTick;
std::unordered_map<unsigned int, sf::Sprite> Entity::spriteMap;
std::unordered_map<unsigned short, std::unordered_map<bool, std::unordered_map<PlayerCountry, std::string>>> playerAttackTree;


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


Entity::EntityObjectAction Entity::getEntityAction() noexcept
{
	const sf::Vector2f pos = getPosition();
	auto ret = EntityObjectAction::NOTHING;
	const auto& entityData = EntityDataStorage::getData(ID);

	// If on screen
	if (!(pos.x + entityData.spriteData.getBounds().width / 2.f < 0 ||              // Off the left
		  pos.y + entityData.spriteData.getBounds().height / 2.f < 0 ||              // Off the top
		  pos.x - entityData.spriteData.getBounds().width / 2.f >= windowSize.width || // Off the right
		  pos.y - entityData.spriteData.getBounds().height / 2.f >= windowSize.height)) // Off the bottom
	{
		if ((entityFlags & 0b00000001) != 0b00000001) // If not spawned
		{
			// Set the hasSpawned flag
			entityFlags |= 0b00000001;

			// Generate a new sprite
			spriteMap.emplace(UUID, sf::Sprite(*entityData.spriteData.getTexture()));

			// Set this entities sprite address
			sprite = &spriteMap.at(UUID);

			sprite->setTextureRect(entityData.spriteData.getBounds());
			vel = entityData.velocity;
		}
		// Is on screen, do not delete.
		ret = EntityObjectAction::DRAW;

		// Maintains action of "NOTHING" if it has been 'spawned' and is still on screen.
		// ^ WHY??? they are insta deleted first tick of game LOL. Moved down to outer if - ninjune
	}
	// If not on screen and has spawned
	else if ((entityFlags & 0b00000001) == 0b00000001 && !levelEditorActive)
		// Not on screen, please delete.
		ret = EntityObjectAction::DELETE;

	return ret;
}


void Entity::move() noexcept
{
	pos += sf::Vector2f(vel.x*(*currentTick-spawnTick), vel.y*(*currentTick-spawnTick));
	if (sprite != nullptr)
		sprite->setPosition(pos);
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
	const short frameCount = EntityDataStorage::getData(ID).spriteData.getCount();

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