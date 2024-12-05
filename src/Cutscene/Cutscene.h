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
	//attacking countries
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

	//useable countries
	enum Country
	{
		STATES,
		JAPAN,
		SWEDEN,
		ENGLAND
	};

	//draws cutscenes
	void draw(int, int, int, sf::RenderWindow&);
	//go check Cutscene.cpp for comments on this stuff cys im lazy
	void startTimer();
	void levelBeat(int);
	bool isDone();
private:

	//indications of which levels have been beat so far
	bool lvlBeat[7] = { false,false,false,false,false,false,false };

	//needed it to be set to something literally can be any number other than 0-8
	int lastLvl = 365;

	//all dialog for cutscenes organized
	std::string dialog[4][9][3][6];
	//font
	sf::Font font;
	//the current cutscenes text for dialog
	sf::Text textDia[6];
	//the current countries players being used
	sf::Texture playersText[4][2];
	sf::Sprite playersSprite[2];
	//indication for a beat level
	sf::Texture lvlBeatTxt;
	sf::Sprite lvlBeatSprite;
	//background map thing where stuff is
	sf::Sprite sprMap;
	sf::Texture txtMap;
	//indicater for next level
	sf::Texture targetText[2];
	sf::Sprite targetSprite;
	//timer for timing things
	sf::Clock timer;
	//WE BRING THE BOOM THATS WHAT WE DO
	sf::Texture explosionTxt[16];
	sf::Sprite explosion;

};

