#pragma once
#include <SFML/Graphics.hpp>

enum class Countries
{
	STATES,
	JAPAN,
	SWEDEN,
	ENGLAND
};

//used to determine what cutscene is used AND holds the value of the last frame for that respective cutscene
enum cutsceneID
{
	START = 3200,
	OSARU = 536,
	PANDORA = 1991,
	KEATON = 645,
	KEATH = 567,
	STATES = 705,
	HEIN = 843,
	MAO = 568,
	JAPAN = 555,
	KOHFUL = 746,
	TEEBEE = 633,
	SWEDEN = 661,
	VILLIAM = 680,
	WHITE = 731,
	ENGLAND = 846
};


/// <summary>
/// holds the data needed for a video cutscene (ones with complex animations that we could not recreate) and provides tools to handle said cutscenes.
/// </summary>
class VideoCutscene
{
public:

	//draws the VideoCutscene to the passed in RenderWindow
	//returns false when the cutscene is over, when the index is on the last frame
	bool draw(sf::RenderWindow& window, cutsceneID id = cutsceneID::START)
	{
		loadImage(id);
		window.draw(frame);
		return index < lastFrame;
	}

	//sets the video back to the beginning.
	void resetVideo() { index = 0; }

	//sets the value of the last frame
	void setLastFrame(cutsceneID id = cutsceneID::START) { lastFrame = id; }

	//things needed to determine the VideoCutscene:
	//if the boss was killed before the time ran out		bool, is this in Game or Level?
	//if it was, which country are we and which				4 options stored in Game
	//players are playing.									3 options stored in Game (p1 p2 or both)
	//if not, which final boss it was						2 options, is this in Game or Level?
	cutsceneID getID(bool bossKilled, bool pandoraWasBoss, int player, Countries country)
	{
		if (bossKilled)
			switch (country)
			{
			case Countries::STATES:
				switch (player)
				{
				case 1:
					return cutsceneID::KEATON;
				case 2:
					return cutsceneID::KEATH;
				case 3:
					return cutsceneID::STATES;
				}
			case Countries::JAPAN:
				switch (player)
				{
				case 1:
					return cutsceneID::HEIN;
				case 2:
					return cutsceneID::MAO;
				case 3:
					return cutsceneID::JAPAN;
				}
			case Countries::SWEDEN:
				switch (player)
				{
				case 1:
					return cutsceneID::KOHFUL;
				case 2:
					return cutsceneID::TEEBEE;
				case 3:
					return cutsceneID::SWEDEN;
				}
			case Countries::ENGLAND:
				switch (player)
				{
				case 1:
					return cutsceneID::VILLIAM;
				case 2:
					return cutsceneID::WHITE;
				case 3:
					return cutsceneID::ENGLAND;
				}
			}
		else
			if (pandoraWasBoss)
				return cutsceneID::PANDORA;
			else
				return cutsceneID::OSARU;
	}

private:
	unsigned short lastFrame, index;
	sf::Texture image; //i moved image to here, if we are only loading one at a time this makes it easy - Christian
	sf::Sprite frame;

	void loadImage(cutsceneID id)
	{
		//the while loop keeps increasing the index variable until it finds a successful load.
		switch (id)
		{
		case cutsceneID::START:
			while (!image.loadFromFile("intro" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::OSARU:
			while (!image.loadFromFile("osaru" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::PANDORA:
			while (!image.loadFromFile("pandora" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KEATON:
			while (!image.loadFromFile("keaton" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KEATH:
			while (!image.loadFromFile("keath" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::STATES:
			while (!image.loadFromFile("states" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::HEIN:
			while (!image.loadFromFile("hein" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::MAO:
			while (!image.loadFromFile("mao" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::JAPAN:
			while (!image.loadFromFile("japan" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KOHFUL:
			while (!image.loadFromFile("kohful" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::TEEBEE:
			while (!image.loadFromFile("teebee" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::SWEDEN:
			while (!image.loadFromFile("sweden" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::VILLIAM:
			while (!image.loadFromFile("villiam" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::WHITE:
			while (!image.loadFromFile("white" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::ENGLAND:
			while (!image.loadFromFile("england" + std::to_string(index++) + ".png")) {}
		}
		frame.setTexture(image);
	}
};

