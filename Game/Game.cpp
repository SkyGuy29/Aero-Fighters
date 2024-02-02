#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}

void Game::run()
{
	win.create(sf::VideoMode(winSize.x * winScale, winSize.y * winScale), "Aero Fighters");
	win.setFramerateLimit(framesPSec);

	level = Level(0);

	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			switch (e.type)
			{
			case sf::Event::Closed:
				win.close();
				break;
			}

		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			playerInput();
		}

		win.clear();

		win.draw(level);

		win.display();
	}
}

void Game::playerInput()
{
	level.movePlayers(
		sf::Vector2f(key(p1Ctrl[Right]) - key(p1Ctrl[Left]), key(p1Ctrl[Back]) - key(p1Ctrl[Forward])),
		sf::Vector2f(key(p2Ctrl[Right]) - key(p2Ctrl[Left]), key(p2Ctrl[Back]) - key(p2Ctrl[Forward])),
		winSize * (unsigned int)winScale);
}

bool Game::key(int k)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
}
