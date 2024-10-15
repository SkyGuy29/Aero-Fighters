#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
//#include "VisualElement.h"
#include "fstream"

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
	//std::queue<VisualElement<sf::Sprite>> spriteElements;
	//std::queue<VisualElement<sf::String>> stringElements;

	//static VisualElement<sf::String> stringElements[4][8][3];
	static bool countries[7];
	std::string dialog[4][8][6];

};

