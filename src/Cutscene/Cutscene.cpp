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
}

Cutscene::~Cutscene()
{

}

void Cutscene::load(int country, int level, int player, sf::RenderWindow&)
{
	//identify which country,players, and level
	
}