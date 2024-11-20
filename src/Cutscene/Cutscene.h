#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string.h>
//#include <Windows.h>
#include <iostream>

class Cutscene
{
public:
	Cutscene();
	~Cutscene();
	enum Map
	{
		England = 0,
		Israel,
		Japan,
		Meddit,
		Russia,
		States,
		Sweden,
		Space
	};

	enum Country
	{
		STATES,
		JAPAN,
		SWEDEN,
		ENGLAND
	};

	void draw(int, int, int, sf::RenderWindow&);
	void startTimer();
	void levelBeat(int);
	bool isDone();
private:

	bool lvlBeat[7] = { false,false,false,false,false,false,false };

	int lastLvl = 365;

	std::string dialog[4][9][3][6];
	sf::Font font;
	sf::Text textDia[6];
	sf::Texture playersText[4][2];
	sf::Sprite playersSprite[2];
	sf::Texture lvlBeatTxt;
	sf::Sprite lvlBeatSprite;
	sf::Sprite sprMap;
	sf::Texture txtMap;
	sf::Texture targetText[2];
	sf::Sprite targetSprite;
	sf::Clock timer;
	sf::Texture explosionTxt[16];
	sf::Sprite explosion;

};

