#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "VisualElement.h"

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
		Sweden
	};
	void load(int, int, bool, bool, sf::RenderWindow&);
	
private:
	std::queue<VisualElement<sf::Sprite>> spriteElements;
	std::queue<VisualElement<sf::String>> stringElements;
	bool countries[7] = { false, false, false, false, false, false, false };

};

