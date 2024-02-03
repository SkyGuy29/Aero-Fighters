#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}

void Game::run()
{
	win.create(sf::VideoMode(winSize.x * winScale, winSize.y * winScale), "Aero Fighters");
	win.setFramerateLimit(framesPSec);


	// This view scales the 224x320 up to whatever the window size is.
	// Just use winSize for calculations, no need to multiply by winScale
	view = win.getDefaultView();
	view.setSize(winSize.x, winSize.y);
	view.setCenter(winSize.x / 2.f, winSize.y / 2.f);

	resize();

	// Due to the weirdness of deconstructors, the old way:
	// level = Level(winSize, 0);
	// would delete the texture before we could use it.
	// I think thats whats happenning, but after 4 hours of debugging this idc it works now.
	// Also for loading res after compiling, the starting directory is the one with the project files.
	// This also was part of the 4 hours.

	level = Level();
	level.load(winSize, 0);

	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
			switch (e.type)
			{
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::Resized:
				resize();
			}

		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			playerInput();
			level.update();
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
		winSize);
}

bool Game::key(int k)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
}

void Game::resize()
{
	winScale = std::fmin(win.getSize().x / winSize.x, win.getSize().y / winSize.y);

	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(win.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(win.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(win.getSize().x),
		winScale * float(winSize.y) / float(win.getSize().y)
	));
	win.setView(view);
}
