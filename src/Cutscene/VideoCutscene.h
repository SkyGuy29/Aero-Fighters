#pragma once
#include <SFML/Graphics.hpp>


//used to determine what cutscene is used AND holds the value of the last frame for that respective cutscene
enum cutsceneID
{
	START = 3200,
	OSARU = 536,
	PANDORA = 1991,
	KEATON = 645,
	KEATH = 567,
	P1P2STATES = 705,
	HEIN = 843,
	MAO = 568,
	P1P2JAPAN = 555,
	KOHFUL = 746,
	TEEBEE = 633,
	P1P2SWEDEN = 661,
	VILLIAM = 680,
	WHITE = 731,
	P1P2ENGLAND = 846
};


/// <summary>
/// holds the data needed for a video cutscene (ones with complex animations that we could not recreate) and provides tools to handle said cutscenes.
/// </summary>
class VideoCutscene
{
public:

	//draws the VideoCutscene to the passed in RenderWindow
	//returns false when the cutscene is over, when the index is on the last frame
	bool draw(sf::RenderWindow& window);

	//sets the video back to the beginning.
	void resetVideo() { index = 0; }

	//sets the id of the cutscene in advance
	void setID(cutsceneID newID) { id = newID; }

	//returns the end cutscene id based on
	cutsceneID getID(bool bossKilled, bool pandoraWasBoss, int player, Countries country);

private:
	unsigned short index;
	cutsceneID id; //used as both the id of the cutscene and the count of the last frame of that cutscene
	sf::Texture image; //i moved image to here, if we are only loading one at a time this makes it easy - Christian
	sf::Sprite frame;

	//loads the image, determined by the cutsceneID
	void loadImage();
};

