#include "Cutscene.h"

bool Cutscene::countries[] = {false, false, false, false, false, false, false};

/*
VisualElement<sf::String> Cutscene::stringElements[4][8][3] =
{
	{
		{
			{
				std::queue<VisualElement<sf::String>> {
					VisualElement<sf::String>{{},{},"",false}
				}
			},
			{},
			{},
		},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
	},
	{},
	{},
	{}
};
*/

Cutscene::Cutscene()
{
	std::fstream englandFile, japanFile, statesFile, swedenFile;
	englandFile.open("englandDialog.txt");
	japanFile.open("japanDialog.txt");
	statesFile.open("statesDialog.txt");
	swedenFile.open("swedenDialog.txt");
	if (englandFile.is_open() && japanFile.is_open() && statesFile.is_open() && swedenFile.is_open())
		for (int i = 0; i < 8; i++)
			for (int z = 0; z < 6; z++)
			{
				std::getline(englandFile, dialog[0][i][z]);
				std::getline(japanFile, dialog[0][i][z]);
				std::getline(statesFile, dialog[0][i][z]);
				std::getline(swedenFile, dialog[0][i][z]);
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