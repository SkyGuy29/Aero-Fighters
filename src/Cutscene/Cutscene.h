#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "VisualElement.h"
#include <fstream>

class Cutscene
{
public:
	Cutscene();
	~Cutscene();
	enum Map
	{
		England,
		Israel,
		Japan,
		Meddit,
		Russia,
		States,
		Sweden,
		Space
	};
	void load(int, int, int, sf::RenderWindow&);
	
private:
	std::queue<VisualElement<sf::Sprite>> spriteElements;
	std::queue<VisualElement<sf::String>> stringElements;

	std::string dialog[8][8][3][6];
};

