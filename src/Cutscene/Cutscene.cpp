#include "Cutscene.h"


Cutscene::Cutscene()
{
	std::fstream englandFile, japanFile, statesFile, swedenFile;
	englandFile.open("englandDialog.txt");
	japanFile.open("japanDialog.txt");
	statesFile.open("statesDialog.txt");
	swedenFile.open("swedenDialog.txt");
	if (englandFile.is_open() && japanFile.is_open() && statesFile.is_open() && swedenFile.is_open())
		for (int l = 0; l < 8; l++)
			for (int p = 0; p < 3; p++)
				for(int d = 0; d < 6; d++)
				{
					std::getline(englandFile, dialog[0][l][p][d]);
					std::getline(japanFile, dialog[2][l][p][d]);
					std::getline(statesFile, dialog[5][l][p][d]);
					std::getline(swedenFile, dialog[6][l][p][d]);
				}
	englandFile.close();
	japanFile.close();
	statesFile.close();
	swedenFile.close();

	font.loadFromFile("aero-fighters.ttf");
	for (int i = 0; i < 6; i++)
	{
		textDia[i].setFont(font);
	}
	textDia[0].setPosition(23, 237);
	textDia[3].setPosition(23, 237);
	textDia[1].setPosition(23, 259);
	textDia[4].setPosition(23, 259);
	textDia[2].setPosition(23, 281);
	textDia[5].setPosition(23, 281);


}

Cutscene::~Cutscene()
{

}

void Cutscene::load(int country, int level, int player, sf::RenderWindow& window)
{
	window.clear();
	sf::Clock timer;
	playersSprite[0].setTexture(playersText[country][0]);
	playersSprite[1].setTexture(playersText[country][1]);
	for (int i = 0; i < 6; i++)
		textDia[i].setString(dialog[country][level][player][i]);
	while (timer.getElapsedTime().asSeconds() < 5)
	{
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
		if (timer.getElapsedTime().asSeconds() < 2.5)
		{
			for (int i = 0; i < 3; i++)
				window.draw(textDia[i]);
			window.display();
		}
		else if (timer.getElapsedTime().asSeconds() > 2.5)
		{
			for (int i = 0; i < 3; i++)
				window.draw(textDia[i+3]);
			window.display();
		}
		else
		{
			window.clear();
		}
		
	}
	window.clear();

	
}