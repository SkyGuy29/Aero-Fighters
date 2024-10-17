#include "Entity.h"
#include "../Sprites/SpriteType.h"

// Static member must be defined outside the class definition.
unsigned int Entity::next_uuid = 0;

void Entity::setWinSize(WindowSize& winSize_)
{
	winSize = winSize_;
}


// spawns on the current tick.
Entity::Entity(sf::Vector2f pos, EntityID ID) :
	pos(pos), ID(ID), UUID(next_uuid++), spawnTick(currentTick)
{
	
}


void Entity::setPosition(sf::Vector2f pos)
{
	this->pos = pos;
	if (sprite != nullptr)
		sprite->setPosition(pos);
}


Entity::EntityObjectAction Entity::getEntityAction() noexcept
{
	sf::Vector2f pos = sprite->getPosition();
	EntityObjectAction ret = EntityObjectAction::NOTHING;

	// If on screen
	if (!(pos.x + SpriteDataStorage::getSpriteData(ID).size.x / 2.f < 0 ||              // Off the left
		  pos.y + SpriteDataStorage::getSpriteData(ID).size.y / 2.f < 0 ||              // Off the top
		  pos.x - SpriteDataStorage::getSpriteData(ID).size.x / 2.f >= winSize.width || // Off the right
		  pos.y - SpriteDataStorage::getSpriteData(ID).size.y / 2.f >= winSize.height)) // Off the bottom
	{
		if ((entityFlags & 0b00000001) != 0b00000001) // If not spawned
		{
			// Set the hasSpawned flag
			entityFlags |= 0b00000001;

			// Generate a new sprite
			spriteMap.emplace(UUID, sf::Sprite(SpriteDataStorage::getTexture(ID)));

			// Set this entities sprite address
			sprite = &spriteMap.at(UUID);

			// Is on screen, do not delete.
			ret = EntityObjectAction::DRAW;
		}

		// Maintains action of "NOTHING" if it has been 'spawned' and is still on screen.
	}
	// If not on screen and has spawned
	else if ((entityFlags & 0b00000001) == 0b00000001 && !getLevelEditor())
		// Not on screen, please delete.
		ret = EntityObjectAction::DELETE;

	return ret;
}


void Entity::move() noexcept
{
	pos += sf::Vector2f(vel.x*(currentTick-spawnTick), vel.y*(currentTick-spawnTick));
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
	short frameCount = SpriteDataStorage::getSpriteData(ID).animationFrameCount;

	if (currentFrame >= frameCount * frameRate)
	{
		currentFrame -= frameCount * frameRate;
		animationFinished = true;
	}
	sf::Vector2f texSize = SpriteDataStorage::getSpriteData(ID).size;
	sf::Vector2f texOffset = SpriteDataStorage::getSpriteData(ID).textureOffset;

	// the dividing to an int is needed for the updates per frame delay.
	sprite->setTextureRect(sf::IntRect(
		texOffset.x + (currentFrame / frameRate) * texSize.x
		* !verticalAnimation,
		texOffset.y + (currentFrame / frameRate) * texSize.y
		* verticalAnimation,
		texSize.x, texSize.y));
}