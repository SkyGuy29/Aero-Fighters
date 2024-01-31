#include "Game.h"

Game::Game()
{
}

void Game::run()
{
	win.create(sf::VideoMode(winSize.x * winScale, winSize.y * winScale), "Aero Fighters");
	win.setFramerateLimit(framesPSec);

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

		win.clear();

		win.draw(level);

		win.display();
	}
}
