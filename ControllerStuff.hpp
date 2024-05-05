#pragma once

#include <SFML/Window.hpp>

// TEMPORARY CONTROLS

// Controller test
//https://hcidesign.com/gamepad/

static enum Controller
{
	A,
	B,
	X,
	Y,
	L2,
	R2,
	L1,
	R1,
	Select_BTN,
	Start,
	L3,
	R3,
	D_Up,
	D_Down,
	D_Left,
	D_Right
};

static enum Controls
{
	Forward,
	Left,
	Back,
	Right,
	Shoot,
	Special,
	Spawn,
	FastForward,
	Select,
};

static enum Countries
{
	STATES,
	JAPAN,
	SWEDEN,
	ENGLAND
};

static int p1Ctrl[] =
{
	sf::Keyboard::W, // Forward
	sf::Keyboard::A, // Left
	sf::Keyboard::S, // Back
	sf::Keyboard::D, // Right
	sf::Keyboard::Q, // Shoot
	sf::Keyboard::E,  // Special
	sf::Keyboard::Space, //Spawn
	sf::Keyboard::Tab, // FFW
	sf::Keyboard::Enter, // Select
};

static int p2Ctrl[] =
{
	sf::Keyboard::I, // Forward
	sf::Keyboard::J, // Left
	sf::Keyboard::K, // Back
	sf::Keyboard::L, // Right
	sf::Keyboard::U, // Shoot
	sf::Keyboard::O,  // Special
	sf::Keyboard::Space, //Spawn
	sf::Keyboard::Tab, // FFW
	sf::Keyboard::Enter, // Select
};

// These two are for shortening code
static bool key(int p, int k)
{
	if (p)
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p2Ctrl[k]));
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p1Ctrl[k]));
}

static bool button(int p, int b)
{
	return sf::Joystick::isButtonPressed(p, b);
}

static sf::Vector2f joystick(int p)
{
	sf::Vector2f move;

	move.x = sf::Joystick::getAxisPosition(p, sf::Joystick::X) / 100.f;
	move.y = sf::Joystick::getAxisPosition(p, sf::Joystick::Y) / 100.f;

	// 15% drift reduction
	move.x *= std::abs(move.x) > 0.15;
	move.y *= std::abs(move.y) > 0.15;
	return move;
}