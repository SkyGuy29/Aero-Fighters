#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}

void Game::run()
{
	window.create(sf::VideoMode(winSize.x * 2, winSize.y * 2), "Aero Fighters");
	window.setFramerateLimit(framesPSec);

	// This view scales the 224x320 up to whatever the window size is.
	// Just use winSize for calculations, no need to multiply by winScale
	view = window.getDefaultView();
	view.setSize(winSize.x, winSize.y);
	view.setCenter(winSize.x / 2.f, winSize.y / 2.f);

	resize();

	level.load(winSize, 0);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
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

		window.clear();

		// draw stuff here

		window.draw(level);

		window.display();
	}
}

void Game::resize()
{
	// Get the minimum scale from either x or y
	// This fills the max space possible, then the view is centered on the window.
	float winScale = std::fmin(float(window.getSize().x) / winSize.x, float(window.getSize().y) / winSize.y);

	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(window.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(window.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(window.getSize().x),
		winScale * float(winSize.y) / float(window.getSize().y)
	));
	window.setView(view);
}