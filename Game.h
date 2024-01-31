#pragma once

#include <SFML/Audio.hpp>

#include "Level.h"

class Game
{
public:
	Game();

	void run();

private:
	sf::Clock clock;
	int deltaTime = 0, updatesPSec = 30;

	sf::RenderWindow win;
	sf::Vector2u winSize = sf::Vector2u(224, 320);
	float winScale = 2.f;
	int framesPSec = 30;

	bool isTwoPlayer = false;

	bool inGame = false;

	Level level;
};