#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	font.loadFromFile("res/aero-fighters.ttf");
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

	menuCountdown.setFont(font);
	menuCountdown.setString("0");
	menuCountdown.setPosition(213.25 - menuCountdown.getLocalBounds().width, 0);

	// load menu textures
	menuMap.loadFromFile("Res/Misc/menuMap.png");
	menuMapRect.setSize({202.5, 129.6});
	menuMapRect.setPosition({10.75, 32});
	menuMapRect.setTexture(&menuMap);

	menuFlags.loadFromFile("Res/Misc/menuFlags.png");
	menuFlagsRect.setTextureRect(sf::IntRect(0, 0, 40, 24));
	menuFlagsRect.setSize({ 40, 24 });
	menuFlagsRect.setTexture(&menuFlags);

	menuSelectRect.setSize({40, 24});
	menuSelectRect.setFillColor(sf::Color::Transparent);
	menuSelectRect.setOutlineColor(sf::Color::Green);
	menuSelectRect.setOutlineThickness(2);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			updatesPSec = 600;
		else
			updatesPSec = 30;

		// Keeps constant update rate.
		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			// update stuff here

			if (playerChoose)
				updateMenu();
			else
				level.update(winSize);
		}

		window.clear();

		// draw stuff here

		if (playerChoose)
			drawMenu();
		else
			window.draw(level);

		window.display();
	}
}

void Game::drawMenu()
{
	window.draw(menuMapRect);

	for (int i = 0; i < 4; i++)
	{
		menuFlagsRect.setTextureRect(sf::IntRect(i * 40, 0, 40, 24));
		menuFlagsRect.setPosition(22.5 + i * 45, 180);
		window.draw(menuFlagsRect);
	}

	menuSelectRect.setOutlineThickness(3 * blinkState);
	menuSelectRect.setPosition(22.5 + country * 45, 180);
	window.draw(menuSelectRect);
	window.draw(menuCountdown);
}

void Game::updateMenu()
{
	menuBlinkTimer++;
	if (menuBlinkTimer == menuBlinkRate)
	{
		menuBlinkTimer = 0;
		blinkState = !blinkState;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		playerChoose = 0;
		level.load(winSize, country, 0);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !keyLeft)
		if (country > 0)
			country--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !keyRight)
		if (country < 3)
			country++;

	keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	playerChoose--;
	menuCountdown.setString(std::to_string(playerChoose / updatesPSec));

	if (!playerChoose)
		level.load(winSize, country, 0);
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