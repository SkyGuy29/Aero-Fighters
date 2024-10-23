#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "VisualElement.h"
#include <fstream>
#include <string.h>

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

	bool lvlBeat[8];
	std::string dialog[8][8][3][6];
	sf::Font font;
	sf::Text textDia[6];
	sf::Texture playersText[8][2];
	sf::Sprite playersSprite[2];
	sf::Texture lvlBeatTxt;
	sf::Sprite lvlBeatSprite;
	sf::Texture lvlBoomTxt[3];
	sf::Sprite lvlBoomSprite;


};

