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

		// Keeps constant update rate.
		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			// update stuff here

			level.update(winSize);
		}

		win.clear();

		// draw stuff here

		win.draw(level);

		win.display();
	}
}

void Game::resize()
{
	// Get the minimum scale from either x or y
	// This fills the max space possible, then the view is centered on the window.
	winScale = std::fmin(float(win.getSize().x) / winSize.x, float(win.getSize().y) / winSize.y);

	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(win.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(win.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(win.getSize().x),
		winScale * float(winSize.y) / float(win.getSize().y)
	));
	win.setView(view);
}