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
	// Initialize window
	window.create(sf::VideoMode((int)winSize.x * 2, (int)winSize.y * 2), 
		"Aero Fighters");
	window.setFramerateLimit(framesPSec);

	// This view scales the 224x320 up to whatever the window size is.
	// Just use winSize for calculations, no need to multiply by winScale
	view = window.getDefaultView();
	view.setSize(winSize.x, winSize.y);
	view.setCenter(winSize.x / 2.f, winSize.y / 2.f);

	resize();


	// Initializes Menu Data //
	
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
		// Debug code to allow for speeding up the game
		if (key(0, Controls::FastForward) || button(0, Controller::X))
		{
			level.debugMode();
			updatesPSec = 600;
		}
		else
			updatesPSec = 30;
#endif

		// Keeps constant update rate.
		
		// Unsure how this maintains a constant update rate,
		// If im not mistaken there should be (1000 / TPS) miliseconds between each tick,
		// It appears as if every single tick the game runs (1000 / TPS) ticks per second, or rather 34 times.
		// Is this intended? am i missing something? - Ricky
		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / updatesPSec)
		{
			deltaTime -= 1000 / updatesPSec;

			// update objects here

			// @@TODO@@ 
			// Short being used as bool? if not 0 it will evaluate to true.
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

		// Clear window display
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
		// Draw every flag equally apart
		menuFlagsRect.setTextureRect(sf::IntRect(i * 40, 0, 40, 24));
		menuFlagsRect.setPosition(22.5f + (float)i * 45, 180);
		window.draw(menuFlagsRect);
	}

	// Handle blinkstate for country selection
	menuSelectRect.setOutlineThickness((float)(3 * blinkState));
	menuSelectRect.setPosition(22.5f + (float)country * 45, 180);

	// Draw the manu and the selection outline
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

	// If the blink state timer has reached its end
	if (menuBlinkTimer == menuBlinkRate)
	{
		// Reset it and toggle the blink state
		menuBlinkTimer = 0;
		blinkState = !blinkState;
	}

	// We can move this to the end and have it only reset playerChosoe so that we dont need the early escape; flow is easier to follow and the code is shorter
	// If any menu selection button has been pressed
	if (key(0, Controls::Select) || button(0, Controller::Y))
	{
		// Reset player choose, load the respective level, and early escape
		playerChoose = 0;
		level.load(winSize, country, 0);
		return;
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
		++country % 4;

	// Doesn't switch if the key is held.
	keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		|| joystick(0).x < -0.5f;
	keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		|| joystick(0).x > 0.5f;

	// Decrement the choice timer.
	playerChoose--;

	// Display new menu countdown
	menuCountdown.setString(std::to_string(playerChoose / updatesPSec));

	// Compare to 0 if it isnt a boolean, improves readability.
	// If the player is out of time to choose, load the appropriate level.
	if (playerChoose == 0)
		level.load(winSize, country, 0);
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