#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:

	Animation(int);
	~Animation();
	void update(sf::Sprite&, std::vector<sf::Texture>);
	void update(int, sf::Sprite&, std::vector<sf::Texture>);
private:
	int frames, currentFrame = 0;

};

