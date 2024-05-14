#pragma once

#include <SFML/Audio.hpp>

#include "../Level/Level.h"
#include "../ControllerStuff.hpp"

//Big class that handles the whole game. It is created and ran once in 
//Main.cpp.
//The main game loop runs here.
class Game
{
public:
	//default constructor for Game objects
	Game();

	//opens and handles the game window and game structure
	void run();
	//draws the menu to the window
	void drawMenu();
	//updates the menu based on player input
	void updateMenu();

private:
	//resizes the window automatically
	void resize();

	sf::Clock clock;
	int deltaTime = 0, updatesPSec = 30;

	sf::RenderWindow window;
	sf::View view;
	sf::Vector2u winSize = sf::Vector2u(224, 320);
	int framesPSec = 30;
	int score, highScore;

	Level level;

	sf::Font font;
	sf::Text menuCountdown;

	bool keyLeft = 0, keyRight = 0, blinkState = 0;
	short country = 0;
	short playerChoose = 10 * updatesPSec;
	short menuBlinkRate = 5, menuBlinkTimer = 0;
	sf::Texture menuMap, menuFlags;
	sf::RectangleShape menuMapRect, menuFlagsRect, menuCountDownRect, 
	menuSelectRect;
};