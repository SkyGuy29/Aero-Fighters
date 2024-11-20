#include "Cutscene.h"


Cutscene::Cutscene()
{
	std::ifstream englandFile;
	englandFile.open("res/Dialog/englandDialog.txt");
	if (englandFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(englandFile, dialog[ENGLAND][l][p][d]);
	englandFile.close();

	std::ifstream japanFile;
	japanFile.open("res/Dialog/japanDialog.txt");
	if (japanFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(japanFile, dialog[JAPAN][l][p][d]);
	japanFile.close();

	std::ifstream statesFile;
	statesFile.open("res/Dialog/statesDialog.txt");
	if (statesFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(statesFile, dialog[STATES][l][p][d]);
	statesFile.close();

	std::ifstream swedenFile;
	swedenFile.open("res/Dialog/swedenDialog.txt");
	if (swedenFile.is_open())
		for (int l = 0; l < 9; l++)
			for (int p = 0; p < 3; p++)
				for (int d = 0; d < 6; d++)
					std::getline(swedenFile, dialog[SWEDEN][l][p][d]);
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
	
	explosion.setPosition(-100, -100);

	txtMap.loadFromFile("res/Misc/menuMap.png");
	sprMap.setTexture(txtMap);
	lvlBeatTxt.loadFromFile("res/Misc/lvlBeat.png");
	lvlBeatSprite.setTexture(lvlBeatTxt);

	playersText[ENGLAND][0].loadFromFile("res/Dialog/villiam.png");
	playersText[ENGLAND][1].loadFromFile("res/Dialog/lord white.png");
	playersText[JAPAN][0].loadFromFile("res/Dialog/hein.png");
	playersText[JAPAN][1].loadFromFile("res/Dialog/mao.png");
	playersText[STATES][0].loadFromFile("res/Dialog/keaton.png");
	playersText[STATES][1].loadFromFile("res/Dialog/keath.png");
	playersText[SWEDEN][0].loadFromFile("res/Dialog/kohful.png");
	playersText[SWEDEN][1].loadFromFile("res/Dialog/tee-bee.png");

	playersSprite[0].setPosition(24, 112);
	playersSprite[1].setPosition(120, 112);

	targetText[0].loadFromFile("res/Dialog/target1.png");
	targetText[1].loadFromFile("res/Dialog/target2.png");

	for (int i = 0; i < 16; i++)
		explosionTxt[i].loadFromFile("res/Dialog/Explosion" + std::to_string(i) + ".png");
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

		switch (lastLvl)
		{
		case England:
			explosion.setPosition(82, 16);
			break;
		case Israel:
			explosion.setPosition(108, 32);
			break;
		case Japan:
			explosion.setPosition(168, 24);
			break;
		case Meddit:
			explosion.setPosition(90, 34);
			break;
		case Russia:
			explosion.setPosition(112, 8);
			break;
		case States:
			explosion.setPosition(40, 24);
			break;
		case Sweden:
			explosion.setPosition(92, -4);
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
		case Space:
			targetSprite.setPosition(-100, -100);
		}


		int temp = timer.getElapsedTime().asSeconds() * 3;
		targetSprite.setTexture(targetText[temp % 2]);
		window.draw(targetSprite);

		double otherTemp = timer.getElapsedTime().asSeconds();

		if (otherTemp < 1.)
		{
			window.draw(explosion);
			for (int i = 1; i <= 16; i++)
				if ((i - 1)/16. < otherTemp && i/16. < otherTemp)
					explosion.setTexture(explosionTxt[i-1]);
		}

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
	lastLvl = level;
}

bool Cutscene::isDone()
{
	return timer.getElapsedTime().asSeconds() > 5.;
}
