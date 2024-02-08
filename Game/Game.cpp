#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}

void Game::run()
{
	win.create(sf::VideoMode(winSize.x * winScale, winSize.y * winScale), "Aero Fighters");
	win.setFramerateLimit(framesPSec);

	for (int i = 0; i < 2; i++)
		p[i].setPos(sf::Vector2f(winSize.x * (i ? 0.75f : 0.25f), winSize.y * 0.75f));

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

			for (int i = 0; i < 2; i++)
				p[i].update(winSize);
		}

		win.clear();

		win.draw(level);

		for (int i = 0; i < 2; i++)
			win.draw(p[i]);

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
	// controller controls
	// sorry, I just have one controller right now, but it should work anyways
	sf::Vector2f joy;

	for (int i = 0; i < 2; i++)
	{
		joy.x = sf::Joystick::getAxisPosition(i, sf::Joystick::X) / 100.f;
		joy.y = sf::Joystick::getAxisPosition(i, sf::Joystick::Y) / 100.f;

		// fix drift under 15%
		joy.x *= std::abs(joy.x) > 0.15f;
		joy.y *= std::abs(joy.y) > 0.15f;
		p[i].move(joy, winSize);

	if (button(i, Y))
		p[i].shoot();

	if (button(i, B))
		p[i].special();

	// keyboard controls
	p[i].move(key(i, Right) - key(i, Left), key(i, Back) - key(i, Forward), winSize);

	if (key(i, Shoot))
		p[i].shoot();
	}
}

bool Game::key(int p, int k)
{
	if (p)
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p2Ctrl[k]));
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p1Ctrl[k]));
}

bool Game::button(int p, int b)
{
	return sf::Joystick::isButtonPressed(p, b);
}
