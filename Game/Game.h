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

	void getInput(Player, Player);

	bool key(int p, int k);

	bool button(int p, int b);

	sf::Clock clock;
	int deltaTime = 0, updatesPSec = 30;

	sf::RenderWindow win;
	sf::View view;
	sf::Vector2u winSize = sf::Vector2u(224, 320);
	float winScale = 2.f;
	int framesPSec = 30;

	Level level;

	// TEMPORARY CONTROLS

	// Controller test
	//https://hcidesign.com/gamepad/

	enum Controller
	{
		A,
		B,
		X,
		Y,
		L1,
		R1,
		L2,
		R2,
		Select,
		Start,
		L3,
		R3,
		D_Up,
		D_Down,
		D_Left,
		D_Right
	};

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