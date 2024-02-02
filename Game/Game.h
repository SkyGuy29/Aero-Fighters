#pragma once

#include <SFML/Audio.hpp>

#include "../Level/Level.h"

class Game
{
public:
	Game();

	void run();

private:
	void playerInput();

	bool key(int k);

	sf::Clock clock;
	int deltaTime = 0, updatesPSec = 30;

	sf::RenderWindow win;
	sf::Vector2u winSize = sf::Vector2u(224, 320);
	float winScale = 2.f;
	int framesPSec = 30;

	bool inGame = false;

	Level level;

	// TEMPORARY CONTROLS

	enum Controls
	{
		Forward,
		Left,
		Back,
		Right,
		Shoot,
		Special
	};

	int p1Ctrl[6] =
	{
		sf::Keyboard::W, // Forward
		sf::Keyboard::A, // Left
		sf::Keyboard::S, // Back
		sf::Keyboard::D, // Right
		sf::Keyboard::Q, // Shoot
		sf::Keyboard::E  // Special
	};

	int p2Ctrl[6] =
	{
		sf::Keyboard::I, // Forward
		sf::Keyboard::J, // Left
		sf::Keyboard::K, // Back
		sf::Keyboard::L, // Right
		sf::Keyboard::U, // Shoot
		sf::Keyboard::O  // Special
	};
};