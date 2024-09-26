#pragma once

#include "../Level/Level.h"
#include <cmath>


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
	STATES1,
	STATES2,
	STATES,
	JAPAN1,
	JAPAN2,
	JAPAN,
	SWEDEN1,
	SWEDEN2,
	SWEDEN,
	ENGLAND1,
	ENGLAND2,
	ENGLAND
};


struct VideoCutscene
{
	void load(cutsceneID);
	void unload();
	void draw(sf::RenderWindow&);
	cutsceneID getID(bool player, bool win);
	unsigned short count, index;
	sf::Sprite* frames;
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
		// Also unsure what it does... - ricky
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
};