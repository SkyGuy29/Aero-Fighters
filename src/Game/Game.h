#pragma once

#include "../Level/Level.h"
#include "../Cutscene/VideoCutscene.h"
#include "../Cutscene/Cutscene.h"
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


enum class Menu
{
	INTRO,
	SELECT,
	LEVEL,
	MISSION,
	LEADERBOARD,
	END
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
private:
	//returns true if changes were made
	bool changeMenu(Menu newMenu);

	void updateSelectMenu();
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
		// The world map seen in the select menu
		menuMapRect,
		// Flags seen in the select menu
		menuFlagsRect,
		// Selection outline (the green guy that flickers)
		menuSelectRect;

	//The video cutscene, works for any of them. will be reloaded for each new one.
	VideoCutscene video;

	//the mission cutscene, works for any of them. will be reloaded for each new one.
	Cutscene cutscene;

	// The game level
	Level level;

	// Last Tick Processing Time
	int deltaTime = 0,
		// Ticks per second
		ticksPerSec = 30,
		// Frames per second
		framesPerSec = 30,
		//player 1 = 0, player2 = 1, player 1 and 2 = 2
		players = 0;

	//int score, highScore;
		 // Is Left Key pressed
	bool keyLeft = false,
		// Is Right Key Pressed
		keyRight = false,
		// Selection menu outline blinking
		blinkState = false,
		// Level editor debug mode
		levelEditor = false,
		selKeyReleased = true;

	// Selected Country
	unsigned char country = 0,
		// The rate at which the blink state changes in ticks
		menuBlinkRate = 5,
		// Current progress int he blink rate
		menuBlinkTimer = 0;

	Countdown countryCountdown, continueCount;

	Menu currentMenu = Menu::INTRO;
	Map currentLevel = Map::England;
	std::vector<Map> completedLevels;

	bool videoDraw = true;

	bool playersDead = false;

	bool debugSkipToBoss = !!!!!true; //!!!false;
};
