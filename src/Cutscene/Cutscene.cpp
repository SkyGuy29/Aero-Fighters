#include "Cutscene.h"


Cutscene::Cutscene()
{
	std::ifstream englandFile;
	englandFile.open("res/Cutscenes/Dialog/englandDialog.txt");
	if (englandFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(englandFile, dialog[England][l][p][d]);
	englandFile.close();

	std::ifstream japanFile;
	japanFile.open("res/Cutscenes/Dialog/japanDialog.txt");
	if (japanFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(japanFile, dialog[Japan][l][p][d]);
	japanFile.close();

	std::ifstream statesFile;
	statesFile.open("res/Cutscenes/Dialog/statesDialog.txt");
	if (statesFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(statesFile, dialog[States][l][p][d]);
	statesFile.close();

	std::ifstream swedenFile;
	swedenFile.open("res/Cutscenes/Dialog/swedenDialog.txt");
	if (swedenFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(swedenFile, dialog[Sweden][l][p][d]);
	swedenFile.close();

	font.loadFromFile("res/aero-fighters.ttf");
	for (int i = 0; i < 6; i++)
	{
		textDia[i].setFont(font);
		textDia[i].setCharacterSize(8);
		textDia[i].setFillColor(sf::Color::White);
		textDia[i].setScale(textDia[i].getScale().x, textDia[i].getScale().y * 3. / 2);
	}
	textDia[0].setPosition(23, 237);
	textDia[3].setPosition(23, 237);
	textDia[1].setPosition(23, 259);
	textDia[4].setPosition(23, 259);
	textDia[2].setPosition(23, 281);
	textDia[5].setPosition(23, 281);

	txtMap.loadFromFile("res/Misc/menuMap.png");
	sprMap.setTexture(txtMap);
	lvlBeatTxt.loadFromFile("res/Misc/lvlBeat.png");
	lvlBeatSprite.setTexture(lvlBeatTxt);

	playersText[England][0].loadFromFile("res/Cutscenes/Dialog/villiam.png");
	playersText[England][1].loadFromFile("res/Cutscenes/Dialog/lord white.png");
	playersText[Japan][0].loadFromFile("res/Cutscenes/Dialog/hein.png");
	playersText[Japan][1].loadFromFile("res/Cutscenes/Dialog/mao.png");
	playersText[States][0].loadFromFile("res/Cutscenes/Dialog/keaton.png");
	playersText[States][1].loadFromFile("res/Cutscenes/Dialog/keath.png");
	playersText[Sweden][0].loadFromFile("res/Cutscenes/Dialog/kohful.png");
	playersText[Sweden][1].loadFromFile("res/Cutscenes/Dialog/tee-bee.png");

	playersSprite[0].setPosition(24, 112);
	playersSprite[1].setPosition(120, 112);

	targetText[0].loadFromFile("res/Cutscenes/Dialog/target1.png");
	targetText[1].loadFromFile("res/Cutscenes/Dialog/target2.png");
}

Cutscene::~Cutscene()
{

}

void Cutscene::draw(int country, int level, int player, sf::RenderWindow& window)
{
	playersSprite[0].setTexture(playersText[country][0]);
	playersSprite[1].setTexture(playersText[country][1]);
	if (!lvlBeat[0] && !lvlBeat[1] && !lvlBeat[2] && !lvlBeat[3] && !lvlBeat[4] && !lvlBeat[5] && !lvlBeat[6])
		for (int i = 0; i < 6; i++)
			textDia[i].setString(dialog[country][8][player][i]);
	else
		for (int i = 0; i < 6; i++)
			textDia[i].setString(dialog[country][level][player][i]);
	if (timer.getElapsedTime().asSeconds() < 5)
	{
		window.draw(sprMap);
		if (lvlBeat[England])
		{
			lvlBeatSprite.setPosition(98, 32);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[Israel])
		{
			lvlBeatSprite.setPosition(124, 48);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[Japan])
		{
			lvlBeatSprite.setPosition(184, 40);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[Meddit])
		{
			lvlBeatSprite.setPosition(106, 50);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[Russia])
		{
			lvlBeatSprite.setPosition(128, 24);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[States])
		{
			lvlBeatSprite.setPosition(56, 40);
			window.draw(lvlBeatSprite);
		}
		if (lvlBeat[Sweden])
		{
			lvlBeatSprite.setPosition(108, 12);
			window.draw(lvlBeatSprite);
		}

		switch (player)
		{
		case 0:
			window.draw(playersSprite[0]);
			break;
		case 1:
			window.draw(playersSprite[1]);
			break;
		case 2:
			window.draw(playersSprite[0]);
			window.draw(playersSprite[1]);
			break;
		}

		switch (level)
		{
		case England:
			targetSprite.setPosition(98, 32);
			break;
		case Israel:
			targetSprite.setPosition(124, 48);
			break;
		case Japan:
			targetSprite.setPosition(184, 40);
			break;
		case Meddit:
			targetSprite.setPosition(106, 50);
			break;
		case Russia:
			targetSprite.setPosition(128, 24);
			break;
		case States:
			targetSprite.setPosition(56, 40);
			break;
		case Sweden:
			targetSprite.setPosition(108, 12);
			break;
		}

		int temp = timer.getElapsedTime().asSeconds() * 3;
		targetSprite.setTexture(targetText[temp % 2]);
		window.draw(targetSprite);

		if (timer.getElapsedTime().asSeconds() < 2.5)
		{
			for (int i = 0; i < 3; i++)
				window.draw(textDia[i]);
		}
		else if (timer.getElapsedTime().asSeconds() > 2.5)
		{
			for (int i = 0; i < 3; i++)
				window.draw(textDia[i + 3]);
		}

	}
}

void Cutscene::startTimer()
{
	timer.restart();
}

void Cutscene::levelBeat(int level)
{
	lvlBeat[level] = true;
}