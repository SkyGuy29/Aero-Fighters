#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "VisualElement.h"

class Cutscene
{
public:
	Cutscene();
	~Cutscene();
	
private:
	std::queue<VisualElement<sf::Sprite>> spriteElements;
	std::queue<VisualElement<sf::String>> stringElements;
};

