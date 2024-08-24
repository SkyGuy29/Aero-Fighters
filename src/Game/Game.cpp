#include "Game.h"


Game::Game()
{
	srand(time(0));

	font.loadFromFile("res/aero-fighters.ttf");
}


/// <summary>
/// Runs the primary gameplay loop.
/// </summary>
void Game::run()
{
	window.create(sf::VideoMode((int)winSize.x * 2, (int)winSize.y * 2), 
		"Aero Fighters");
	window.setFramerateLimit(framesPSec);

	// This view scales the 224x320 up to whatever the window size is.
	// Just use winSize for calculations, no need to multiply by winScale
	view = window.getDefaultView();
	view.setSize(winSize.x, winSize.y);
	view.setCenter(winSize.x / 2.f, winSize.y / 2.f);

	resize();

	menuCountdown.setFont(font);
	menuCountdown.setString("0");
	menuCountdown.setPosition(213.25f - menuCountdown.getLocalBounds().width, 
		0);

	// load menu textures
	menuMap.loadFromFile("res/Misc/menuMap.png");
	menuMapRect.setSize({202.5f, 129.6f});
	menuMapRect.setPosition({10.75f, 32.f});
	menuMapRect.setTexture(&menuMap);

	menuFlags.loadFromFile("res/Misc/menuFlags.png");
	menuFlagsRect.setTextureRect(sf::IntRect(0, 0, 40, 24));
	menuFlagsRect.setSize({ 40, 24 });
	menuFlagsRect.setTexture(&menuFlags);

	menuSelectRect.setSize({40, 24});
	menuSelectRect.setFillColor(sf::Color::Transparent);
	menuSelectRect.setOutlineColor(sf::Color::Green);
	menuSelectRect.setOutlineThickness(2);

	// Primary gameplay loop
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resize();
			}
		}
			
#ifdef _DEBUG
		if (key(0, Controls::FastForward) || button(0, Controller::X))
		{
			level.debugMode();
			updatesPSec = 600;
		}
		else
			updatesPSec = 30;
#endif

		// Keeps constant update rate.
		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			// update objects here

			if (playerChoose)
				updateMenu();
			else
			{
				// level::update() runs most of the gameplay.
				if (!level.update(winSize))
				{
					// Player death here. NEEDS UPDATE
					sf::sleep(sf::milliseconds(1000)); 

					printf("You lost!\n");
					window.close();
				}
			}
		}

		window.clear();

		// draw objects here

		if (playerChoose)
			drawMenu();
		else
			window.draw(level);

		window.display();
	}
}


/// <summary>
/// Draws the country select menu.
/// </summary>
void Game::drawMenu()
{
	window.draw(menuMapRect);

	for (int i = 0; i < 4; i++)
	{
		menuFlagsRect.setTextureRect(sf::IntRect(i * 40, 0, 40, 24));
		menuFlagsRect.setPosition(22.5f + (float)i * 45, 180);
		window.draw(menuFlagsRect);
	}

	menuSelectRect.setOutlineThickness((float)(3 * blinkState));
	menuSelectRect.setPosition(22.5f + (float)country * 45, 180);
	window.draw(menuSelectRect);
	window.draw(menuCountdown);
}


/// <summary>
/// Updates the country select menu.
/// </summary>
void Game::updateMenu()
{
	// For the number in top right.
	menuBlinkTimer++;

	if (menuBlinkTimer == menuBlinkRate)
	{
		menuBlinkTimer = 0;
		blinkState = !blinkState;
	}

	// Checks if country has been selected
	if (key(0, Controls::Select) || button(0, Controller::Y))
	{
		playerChoose = 0;
		level.load(winSize, country, 0);
		return;
	}

	// Switches between countries
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		|| joystick(0).x < -0.5f) && !keyLeft)
		if (country > 0)
			country--;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		|| joystick(0).x > 0.5f) && !keyRight)
		if (country < 3)
			country++;

	// Doesn't switch if the key is held.
	keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		|| joystick(0).x < -0.5f;
	keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		|| joystick(0).x > 0.5f;

	playerChoose--;
	menuCountdown.setString(std::to_string(playerChoose / updatesPSec));

	if (!playerChoose)
		level.load(winSize, country, 0);
}


/// <summary>
/// Resizes the game window.
/// </summary>
void Game::resize()
{
	// Get the minimum scale from either x or y
	// This fills the max space possible, then the view is centered on the window.
	const float winScale = std::fmin(float(window.getSize().x) / (float)winSize.x,
		float(window.getSize().y) / (float)winSize.y);

	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(window.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(window.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(window.getSize().x),
		winScale * float(winSize.y) / float(window.getSize().y)
	));
	window.setView(view);
}