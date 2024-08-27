#pragma once

#include <SFML/Window.hpp>

// TEMPORARY CONTROLS

// Controller test
//https://hcidesign.com/gamepad/

// SFML controls are kind of messed up
// dpad is POVx and POVy https://en.sfml-dev.org/forums/index.php?topic=7412.0
enum Controller : unsigned char
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

enum Controls
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

enum Countries
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

/// <summary>
/// Checks if a key is pressed using the controls for players 1 and 2.
/// </summary>
/// <param name="player">0 and 1 respectively corrospond to players 1 and 2 control schema.</param>
/// <param name="key">The key to check.</param>
/// <returns></returns>
static bool key(int player, Controls key)
{
	if (player)
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p2Ctrl[(unsigned int)key]));
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p1Ctrl[(unsigned int)key]));
}


/// <summary>
/// (May want to change key() to check both the joystick and key)
/// </summary>
/// <param name="player"></param>
/// <param name="button"></param>
/// <returns></returns>
static bool button(int player, int button)
{
	return sf::Joystick::isButtonPressed(player, button);
}


/// <summary>
/// Returns a vector with how much the player should move based on the joystick's position.
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
static sf::Vector2f joystick(int player)
{
	sf::Vector2f move;

	move.x = sf::Joystick::getAxisPosition(player, sf::Joystick::X) / 100.f;
	move.y = sf::Joystick::getAxisPosition(player, sf::Joystick::Y) / 100.f;

	// 15% drift reduction
	move.x *= std::abs(move.x) > 0.15;
	move.y *= std::abs(move.y) > 0.15;
	return move;
}