#pragma once

#include "../Level/Level.h"


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

	sf::RenderWindow window;
	sf::View view;
	sf::Vector2f winSize = sf::Vector2f(224.f, 320.f);
	sf::Clock clock;
	sf::Font font;
	sf::Text menuCountdown;
	sf::Texture menuMap, menuFlags;
	sf::RectangleShape menuMapRect, menuFlagsRect, menuCountDownRect,
		menuSelectRect;
	Level level;

	int deltaTime = 0, updatesPSec = 30, framesPSec = 30;
	//int score, highScore;
	bool keyLeft = false, keyRight = false, blinkState = false;
	short country = 0, menuBlinkRate = 5, menuBlinkTimer = 0;
	// Frames that the player is on menu screen.
	short playerChoose = (short)(10 * updatesPSec);
};