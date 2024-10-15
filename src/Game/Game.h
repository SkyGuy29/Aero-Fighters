#pragma once

#include "../Level/Level.h"
#include <cmath>

/*
#ifdef _WIN32
extern "C" { extern int SetWindowPos(void*, void*, int, int, int, int, unsigned); }
#endif

static void setWindowTopmost(sf::RenderWindow& window)
{
#ifdef _WIN32
	SetWindowPos(window.getSystemHandle(), (void*)(-1), 0, 0, 0, 0, 2 | 1);
#else
	printf("Sorry, setWindowTopmost only supports Win32 at this time.\nChange it here: \"src/Game/Game.h\" | Line:%d\n", __LINE__);
#endif
}
*/


class Countdown
{
public:
	unsigned getTime()
	{
		return seconds;
	}

	bool isDone()
	{
		return (seconds == 0);
	}

	void tick()
	{
		if (seconds > 0)
			progress--;
		if (progress == 0)
		{
			seconds--;
			progress = ticksPerSec;
		}
	}

	void set(unsigned seconds, unsigned ticksPerSec)
	{
		this->seconds = seconds;
		this->ticksPerSec = ticksPerSec;
		this->progress = ticksPerSec;
	}

	void reset()
	{
		this->seconds = 0;
		this->progress = 0;
	}

private:
	unsigned seconds = 0,
		progress = 0,
		ticksPerSec = 0;
};


enum class cutsceneID
{
	START,
	OSARU,
	PANDORA,
	KEATON,
	KEATH,
	STATES,
	HEIN,
	MAO,
	JAPAN,
	KOHFUL,
	TEEBEE,
	SWEDEN,
	VILLIAM,
	WHITE,
	ENGLAND
};


class VideoCutscene
{
public:
	void loadImage(cutsceneID id)
	{
		//the while loop keeps increasing the index variable until it finds a successful load.
		switch (id)
		{
		case cutsceneID::START:
			while (!image.loadFromFile("intro" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::OSARU:
			while (!image.loadFromFile("osaru" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::PANDORA:
			while (!image.loadFromFile("pandora" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::KEATON:
			while (!image.loadFromFile("keaton" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::KEATH:
			while (!image.loadFromFile("keath" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::STATES:
			while (!image.loadFromFile("states" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::HEIN:
			while (!image.loadFromFile("hein" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::MAO:
			while (!image.loadFromFile("mao" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::JAPAN:
			while (!image.loadFromFile("japan" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::KOHFUL:
			while (!image.loadFromFile("kohful" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::TEEBEE:
			while (!image.loadFromFile("teebee" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::SWEDEN:
			while (!image.loadFromFile("sweden" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::VILLIAM:
			while (!image.loadFromFile("villiam" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::WHITE:
			while (!image.loadFromFile("white" + std::to_string(index++) + ".png")){}
			break;
		case cutsceneID::ENGLAND:
			while (!image.loadFromFile("england" + std::to_string(index++) + ".png")){}
		}
		frame.setTexture(image);
	}

	//returns false when the cutscene is over, when the index is on the last frame
	bool draw(sf::RenderWindow& window)
	{
		loadImage(cutsceneID::START);
		window.draw(frame);
		return index < size;
	}

	void resetIndex() { index = 0; }

	//DO NOT USE THIS CLASS UNTIL THIS FUNCTION WORKS
	void initSize(cutsceneID)
	{
		//based on the cutsceneID, check the frame files to see what the last one is.
		//WHILE THE LAST FRAME MAY NOT REPRESENT THE VIDEO SIZE, THAT IS HOW THE SIZE VARIABLE WILL BE USED.
		//i have no idea how to code this other than to use sf::Texture.loadFromFile
		//which is obviously not okay at all
	}

	//things needed to determine the VideoCutscene:
	//if the boss was killed before the time ran out		bool, is this in Game or Level?
	//if it was, which country are we and which				4 options stored in Game
	//players are playing.									3 options stored in Game (p1 p2 or both)
	//if not, which final boss it was						2 options, is this in Game or Level?
	cutsceneID getID(bool bossKilled, bool pandoraWasBoss, int player, int country)
	{
		if (bossKilled)
			switch (country)
			{
			case STATES:
				switch (player)
				{
				case 1:
					return cutsceneID::KEATON;
				case 2:
					return cutsceneID::KEATH;
				case 3:
					return cutsceneID::STATES;
				}
			case JAPAN:
				switch (player)
				{
				case 1:
					return cutsceneID::HEIN;
				case 2:
					return cutsceneID::MAO;
				case 3:
					return cutsceneID::JAPAN;
				}
			case SWEDEN:
				switch (player)
				{
				case 1:
					return cutsceneID::KOHFUL;
				case 2:
					return cutsceneID::TEEBEE;
				case 3:
					return cutsceneID::SWEDEN;
				}
			case ENGLAND:
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
	unsigned short size, index; //should we rename size to lastFrame? might be more clear that way
	sf::Texture image; //i moved image to here, if we are only loading one at a time this makes it easy - Christian
	sf::Sprite frame;
};


/// <summary>
/// Big class that handles the whole game. 
/// It is created and ran once in Main.cpp. 
/// The main game loop runs here.
/// 
/// @@TODO@@
/// Handle inter-object interactions here - Ricky
/// 
/// </summary>
class Game
{
public:
	Game();

	void run();

	void drawMenu();
	void updateMenu();
private:
	void resize();

	// The game window
	sf::RenderWindow window;

	// The size of the window
	sf::Vector2f winSize = sf::Vector2f(224.f, 320.f);

	// The in game view area
	sf::View view;
	float viewportScroll = winSize.y / 2.f;

	// Deltatime clock
	sf::Clock clock;

	// Menu Font
	sf::Font font;

	// Text used to diaplay the menu countdown
	sf::Text menuCountdown;

	// Menu Map texture, unsure what it does? - Ricky
	sf::Texture menuMap,
		// Also unsure what it does... - Ricky
		menuFlags;

	// These should all be wrapped in a struct to structure the data; make it easier to understand its all related
	sf::RectangleShape
		// The naming scheme is misleading, this appears to be the background of the menu? - ricky
		menuMapRect,
		// Used for chosing the country? - ricky
		menuFlagsRect,
		// Only ever declared, never used... Delete it - Ricky
		menuCountDownRect,
		// Selection outline
		menuSelectRect;

	// The game level
	Level level;

	// Last Tick Processing Time
	int deltaTime = 0,
		// Ticks per second
		ticksPerSec = 30,
		// Frames per second
		framesPerSec = 30;

	//int score, highScore;
		 // Is Left Key pressed
	bool keyLeft = false,
		// Is Right Key Pressed
		keyRight = false,
		// Selection menu outline blinking
		blinkState = false,
		// Level editor debug mode
		levelEditor = false;

	// Selected Country
	unsigned char country = 0,
		// The rate at which the blick state changes in ticks
		menuBlinkRate = 5,
		// Current progress int he blink rate
		menuBlinkTimer = 0;

	Countdown countryChoose, gameOver;

	bool inGame = false, playersDead = false;

	bool debugSkipToBoss = !!!!!true; //!!!false;
};
