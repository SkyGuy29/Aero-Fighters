#include "Game.h"


Game::Game()
{
	long long seed = time(nullptr);

	srand(
		seed < 0 // If seed is negative
		? (seed *= -1) %= std::numeric_limits<unsigned int>::max()
		: seed %= std::numeric_limits<unsigned int>::max());

	// Initialize window
	window.create(sf::VideoMode((int)winSize.x * 2, (int)winSize.y * 2),
		"Aero Fighters");
	window.setFramerateLimit(framesPerSec);

	// This view scales the 224x320 up to whatever the window size is.
	// Just use winSize for calculations, no need to multiply by winScale
	view = window.getDefaultView();
	view.setSize(winSize.x, winSize.y);
	view.setCenter(winSize.x / 2.f, winSize.y / 2.f);

	resize();


	// Initializes Menu Data //

	menuCountdown.setFont(font);
	menuCountdown.setString("0");
	menuCountdown.setPosition(213.25f - menuCountdown.getLocalBounds().width, 0);

	// load menu textures
	menuMap.loadFromFile("res/Misc/menuMap.png");
	menuMapRect.setSize({ 202.5f, 129.6f });
	menuMapRect.setPosition({ 10.75f, 32.f });
	menuMapRect.setTexture(&menuMap);

	menuFlags.loadFromFile("res/Misc/menuFlags.png");
	menuFlagsRect.setTextureRect(sf::IntRect(0, 0, 40, 24));
	menuFlagsRect.setSize({ 40, 24 });
	menuFlagsRect.setTexture(&menuFlags);

	menuSelectRect.setSize({ 40, 24 });
	menuSelectRect.setFillColor(sf::Color::Transparent);
	menuSelectRect.setOutlineColor(sf::Color::Green);
	menuSelectRect.setOutlineThickness(2);

	font.loadFromFile("res/aero-fighters.ttf");
}


/// <summary>
/// Runs the primary gameplay loop.
/// </summary>
void Game::run()
{
	countryChoose.set(10, ticksPerSec);

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
		// Debug code to allow for speeding up the game
		if (key(0, Controls::FastForward) || button(0, Controller::X))
		{
			level.debugMode();
			ticksPerSec = 600;
		}
		else
			ticksPerSec = 30;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !levelEditor &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !countryChoose.isDone())
		{
			levelEditor = true;
			// static casts are annyoing to look at
			window.setSize(sf::Vector2u(
				static_cast<unsigned int>(winSize.x) * 4,
				static_cast<unsigned int>(winSize.y) * 2)
			);

		}
#endif

		// Keeps constant update rate.

		// Unsure how this maintains a constant update rate,
		// If im not mistaken there should be (1000 / TPS) miliseconds between each tick,
		// It appears as if every single tick the game runs (1000 / TPS) ticks per second, or rather 34 times.
		// Is this intended? am i missing something? - Ricky

		// In the rare event that the game lags behind, it will not catch up. 
		// sfml's frame delay only slows down the game, but can't speed it up to catch up.
		// If we actually put this on some arcade machine, this will be needed.
		// If you really want this gone, the only code that directly uses this is the debug speedup,
		// Which is right above this. -Ben
		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / ticksPerSec)
		{
			deltaTime -= 1000 / ticksPerSec;

			// update objects here

			// If in game and players alive:
			//	update level
			//	render level
			// If not in game and players alive:
			//	update menu (start)
			//	render menu(start)
			// If not in game and players dead:
			//	update menu (game over)
			//	render level, then render menu(game over)

			// Start -> playersDead = false, inGame = false
			// Main menu choice -> inGame = true
			// Both players out of lives -> playersDead = false, inGame = false
			// Game over countdown ends -> playersDead = true
			// -Ben

			if (inGame)
			{
				// level::update() runs most of the gameplay.
				if (!level.update(winSize))
				{
					gameOver.set(10, ticksPerSec);
					playersDead = true;
					inGame = false;
				}
			}
			else
			{
				countryChoose.tick();
				gameOver.tick();
				updateMenu();
			}
		}

		// Clear window display
		window.clear();

		// draw objects here

		// Draw the level gameplay if players are playing or dead
		if (inGame || playersDead)
			window.draw(level);
		// This does have to be it's own 'if' so the game over screen can overlay the gameplay
		if (!inGame)
			drawMenu();

		window.display();
	}
}


/// <summary>
/// Draws the country select menu.
/// </summary>
void Game::drawMenu()
{
	if (playersDead) // Game over menu
	{
		menuCountdown.setPosition((winSize - menuCountdown.getLocalBounds().getSize()) / 2.f);

		window.draw(menuCountdown);
	}
	else // Start menu
	{
		window.draw(menuMapRect);

		for (int i = 0; i < 4; i++)
		{
			// Draw every flag equally apart
			menuFlagsRect.setTextureRect(sf::IntRect(i * 40, 0, 40, 24));
			menuFlagsRect.setPosition(22.5f + (float)i * 45, 180);
			window.draw(menuFlagsRect);
		}

		// Handle blinkstate for country selection
		menuSelectRect.setOutlineThickness((float)(3 * blinkState));
		menuSelectRect.setPosition(22.5f + (float)country * 45, 180);

		menuCountdown.setPosition(213.25f - menuCountdown.getLocalBounds().width, 0);

		// Draw the manu and the selection outline
		window.draw(menuSelectRect);
		window.draw(menuCountdown);
	}
}


/// <summary>
/// Updates the country select menu.
/// </summary>
void Game::updateMenu()
{
	if (playersDead) // Game over menu
	{
		menuCountdown.setString(std::to_string(gameOver.getTime()));

		if (key(0, Controls::Select) || button(0, Controller::Select_BTN))
		{
			playersDead = false;
			inGame = true;
			level.respawnPlayers();
		}

		// Return to main menu for now, probably cutscene later
		if (gameOver.isDone())
		{
			playersDead = false;
			countryChoose.set(10, ticksPerSec);
		}
	}
	else // Start menu
	{
		// For the number in top right.
		menuBlinkTimer++;

		// If the blink state timer has reached its end
		if (menuBlinkTimer == menuBlinkRate)
		{
			// Reset it and toggle the blink state
			menuBlinkTimer = 0;
			blinkState = !blinkState;
		}

		// Switches between countries
		// If wrapping is unwanted this can all be easily reverted. - ricky
		// If menu selection should move to the left
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| joystick(0).x < -0.5f) && !keyLeft)
			// Move country selection to the left with wrapping
			(country == 0 ? country = 3 : country--);

		// Else if menu selection should move to the right
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| joystick(0).x > 0.5f) && !keyRight)
			// Move country selection to the right with wrapping
			++country %= 4;

		// Doesn't switch if the key is held.
		keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| joystick(0).x < -0.5f;
		keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| joystick(0).x > 0.5f;

		// Display new menu countdown
		menuCountdown.setString(std::to_string(countryChoose.getTime()));


		// We can move this to the end and have it only reset playerChosoe so that we dont need the early escape; flow is easier to follow and the code is shorter
		// If time is out or any menu selection button has been pressed
		if (countryChoose.isDone() || key(0, Controls::Select) || button(0, Controller::Y))
		{
			// Reset player choose, load the respective level, and early escape
			countryChoose.reset();
			inGame = true;
			level.load(winSize, country, Level::England, levelEditor); // Set the last param for loading the correct map
		}
	}
}


/// <summary>
/// Resizes the game window.
/// </summary>
void Game::resize()
{
	// Get the minimum scale from either x or y
	// This fills the max space possible, then the view is centered on the window.
	// Generate scaling factor based the dimension closest to its respective value in the size pair.
	const float winScale = std::fmin(float(window.getSize().x) / (float)winSize.x,
		float(window.getSize().y) / (float)winSize.y);

	// Center the viewport
	view.setViewport(sf::FloatRect(
		0.5f - winScale * float(winSize.x) / float(window.getSize().x) / 2.f,
		0.5f - winScale * float(winSize.y) / float(window.getSize().y) / 2.f,
		winScale * float(winSize.x) / float(window.getSize().x),
		winScale * float(winSize.y) / float(window.getSize().y)
	));
	// Update the window
	window.setView(view);
}