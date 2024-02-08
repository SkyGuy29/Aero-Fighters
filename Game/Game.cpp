#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}

void Game::run()
{
	win.create(sf::VideoMode(winSize.x * winScale, winSize.y * winScale), "Aero Fighters");
	win.setFramerateLimit(framesPSec);

	p1.setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	p2.setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

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

		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			level.update(winSize);
			getInput();

			p1.update(winSize);
			p2.update(winSize);
		}

		win.clear();

		win.draw(level);

		win.draw(p1);
		win.draw(p2);

		win.display();
	}
}

void Game::resize()
{
	winScale = std::fmin(float(win.getSize().x) / winSize.x, float(win.getSize().y) / winSize.y);

	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(win.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(win.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(win.getSize().x),
		winScale * float(winSize.y) / float(win.getSize().y)
	));
	win.setView(view);
}

void Game::getInput()
{
	p1.move(key(p1Ctrl[Right]) - key(p1Ctrl[Left]), key(p1Ctrl[Back]) - key(p1Ctrl[Forward]), winSize);
	p2.move(key(p2Ctrl[Right]) - key(p2Ctrl[Left]), key(p2Ctrl[Back]) - key(p2Ctrl[Forward]), winSize);

	if (key(p1Ctrl[Shoot]))
		p1.shoot();
	if (key(p2Ctrl[Shoot]))
		p2.shoot();
}

bool Game::key(int k)
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(k));
}