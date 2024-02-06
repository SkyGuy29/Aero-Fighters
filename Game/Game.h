#pragma once

#include <SFML/Audio.hpp>

#include "../Level/Level.h"

class Game
{
public:
	Game();

	void run();

private:
	void resize();

	sf::Clock clock;
	int deltaTime = 0, updatesPSec = 30;

	sf::RenderWindow win;
	sf::View view;
	sf::Vector2u winSize = sf::Vector2u(224, 320);
	float winScale = 2.f;
	int framesPSec = 30;

	bool inGame = false;

	Level level;
};