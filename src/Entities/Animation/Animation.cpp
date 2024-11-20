#include "Animation.h"

Animation::Animation(int numberOfFrames)
{
	frames = numberOfFrames;
}

Animation::~Animation()
{

}

void Animation::update(sf::Sprite& thing, std::vector<sf::Texture> textures)
{
	currentFrame++;
	update(currentFrame % frames, thing, textures);
}

void Animation::update(int newFrame, sf::Sprite& thing, std::vector<sf::Texture> textures)
{
	thing.setTexture(textures[newFrame]);
}
