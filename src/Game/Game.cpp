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

	//Object::setView(view);
	//Level::setView(view);

	resize();
	level = new Level(window);

	// Initializes Menu Data
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

	// debugging always on top window
	// can't see window while exec paused
	//setWindowTopmost(window);
}

Game::~Game()
{
	delete level;
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
			level->debugMode();
			ticksPerSec = 600;
		}
		else
			ticksPerSec = 30;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !levelEditor &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !countryChoose.isDone())
		{
			levelEditorActive = true;
			// static casts are annyoing to look at
			window.setSize(sf::Vector2u(
				static_cast<unsigned int>(winSize.x) * 4,
				static_cast<unsigned int>(winSize.y) * 2)
			);
		}

		//switching menus with equals hotkey
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
				changeMenu(Menu::INTRO);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				changeMenu(Menu::SELECT);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				changeMenu(Menu::LEVEL);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				changeMenu(Menu::MISSION);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				changeMenu(Menu::LEADERBOARD);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				changeMenu(Menu::END);
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
			if (currentMenu == Menu::LEVEL)
			{
				//moving the viewport by viewportScroll pixels
				view.setCenter(winSize.x / 2.f, viewportScroll);
				window.setView(view);
				Level::setView(view);

				//level::update() runs most of the gameplay.
				if (!level->update(winSize))
				{
					//placeholder code, commented out will be the real deal
					if (!playersDead)
						continueCount.set(10, ticksPerSec);
					playersDead = true;
					/*
					if () //game over, both players dead + animations finished, the false is entirely a placeholder as well - Christian
					{
						continueCount.set(10, ticksPerSec);
						playersDead = true;
					}
					else if () //next level, once again false is a placeholder
					{
						completedLevels.push_back(currentLevel);
						changeMenu(Menu::MISSION);
					}
					*/
				}
				else
					viewportScroll -= level.getBackgroundSpeed();

				if (playersDead) // Continue menu
				{
					menuCountdown.setString(std::to_string(continueCount.getTime()));

					if (key(0, Controls::Select) || button(0, Controller::Select_BTN))
					{
						playersDead = false;
						level.respawnPlayers();
					}
					
					continueCount.tick();

					// Return to main menu for now, leaderboard later if we get there
					if (continueCount.isDone())
					{
						changeMenu(Menu::SELECT);
						countryChoose.set(10, ticksPerSec);
						viewportScroll = winSize.y / 2.f;
					}
				}
			}
		}

		//additional updates for menus that arent level since they dont need deltaTime
		switch (currentMenu)
		{
		case Menu::INTRO:
			if (countryChoose.isDone() || key(0, Controls::Select) || button(0, Controller::Y))
			{
				selKeyReleased = false;
				changeMenu(Menu::SELECT);
			}
			break;
		case Menu::SELECT:
			countryChoose.tick();
			updateSelectMenu();
			break;
		case Menu::MISSION:
			//update mission cutscenes for timing animations
			break;
		case Menu::LEADERBOARD:
			//check player input
			break;
		default:
			break;
		}

		if (!(countryChoose.isDone() || key(0, Controls::Select) || button(0, Controller::Y)))
			selKeyReleased = true;

		// Clear window display
		window.clear();

		// draw objects here

		// Draw the level gameplay if players are playing or dead
		//view.setCenter(winSize.x / 2.f, viewportScroll);
		switch (currentMenu)
		{
		case Menu::INTRO:
			if (videoDraw)
				videoDraw = video.drawTo(window); //stop drawing when cutscene is done
			else
			{
				video.resetVideo(); //start cutscene loops, none of the others do tho
				videoDraw = true;
			}
			break;
		case Menu::SELECT:
			view.setCenter(winSize.x / 2.f, winSize.y / 2.f);
			window.setView(view);
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
			break;
		case Menu::LEVEL:
			view.setCenter(winSize.x / 2.f, viewportScroll);
			window.setView(view);
			//Object::setView(view);
			//Level::setView(view);
			window.draw(level);

			if (playersDead) // Game over menu
			{
				view.setCenter(winSize.x / 2.f, winSize.y / 2.f);
				window.setView(view);
				menuCountdown.setPosition((winSize - menuCountdown.getLocalBounds().getSize()) / 2.f);

				window.draw(menuCountdown);
			}
			break;
		case Menu::MISSION:
			break;
		case Menu::LEADERBOARD:
			break;
		case Menu::END:
			break;
		default:
			break;
		}

		window.display();
	}
}


//handles resets needed for sucessful menu changes
bool Game::changeMenu(Menu newMenu)
{
	if (currentMenu != newMenu)
	{
		currentMenu = newMenu;
		switch (newMenu)
		{
		case Menu::INTRO:
			video.setID(cutsceneID::START);
			video.resetVideo();
			break;
		case Menu::SELECT:
			countryChoose.set(10, ticksPerSec);
			break;
		case Menu::LEVEL:
			//load new level, make sure things that need to be reset are reset
			level->load(winSize, country, currentLevel, false);
			break;
		case Menu::MISSION:
			//reset and load the mission cutscene
			//imma leave this one to Ray lol
			//pick next level
			if (completedLevels.size() < 3)
			{
				std::vector<Map> countryMaps;
				countryMaps.push_back(Map::States);
				countryMaps.push_back(Map::Japan);
				countryMaps.push_back(Map::Sweden);
				countryMaps.push_back(Map::England);

				//remove the level for the country you are
				countryMaps.erase(countryMaps.begin() + country);
				//remove any completed levels
				for (int i = 0; i < completedLevels.size(); i++)
				{
					for (int j = 0; j < countryMaps.size(); j++)
					{
						if (countryMaps.at(j) == completedLevels.at(i))
						{
							countryMaps.erase(countryMaps.begin() + j);
						}
					}
				}

				//randomize between remaining
				currentLevel = countryMaps.at(rand() % (countryMaps.size()));
			}
			else
			{
				switch (completedLevels.size())
				{
				case 3:
					currentLevel = Map::Israel;
					break;
				case 4:
					currentLevel = Map::Meddit;
					break;
				case 5:
					currentLevel = Map::Russia;
					break;
				case 6:
					currentLevel = Map::Space;
					break;
				}
			}
			break;
		case Menu::LEADERBOARD:
			//reset leaderboard stuff
			//leave this like this until we actually do something with leaderboard
			break;
		case Menu::END:
			video.setID(video.getID(true, true, 1, Countries::JAPAN)); //i think this would be Mao, placeholder ofc
			video.resetVideo();
			break;
		}

		if (currentMenu != Menu::LEVEL)
		{
			playersDead = false;
			level = Level();
		}

		return true;
	}
	return false;
}


/// <summary>
/// Updates the country select menu.
/// </summary>
void Game::updateSelectMenu()
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
	if (selKeyReleased && (countryChoose.isDone() || key(0, Controls::Select) || button(0, Controller::Y)))
	{
		// Reset player choose, load the respective level, and early escape
		countryChoose.reset();
		currentMenu = Menu::LEVEL;
		level->load(winSize, country, Map::England, levelEditor); // Set the last param for loading the correct map

		if (debugSkipToBoss)
			viewportScroll = level->skipToBoss();
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

/*
* currentMenu starts on INTRO
* cutscene will loop until enter is pressed
* change currentMenu to select
* change to level when enter is pressed and animations are done (countdown?)
* plays level
* game over overlay is NOT a seperate currentMenu, that would make level reload data
* if the game over currentMenu finishes, change to leaderboard
* if the level ends in a win condition, change to mission
* mission switches to level at the end of countdown
* this reapeats until 7 levels have been played
* if the 7th level ends in a win (no game over screen), change to end instead of mission
* end of cutscene, switch to mission and game cycle repeats
*/

/*
start:
	start cutscene
	while (cutscene is not done)
		if (user input)
			goto: countrySelect
	goto: start

countrySelect:
	start countdown at 10s
	while (countdown is not done)
		if (user select)
			goto: level
	goto: level

level:
	start level
levelUpdate:
	while (players alive and boss alive)
		update game

	if (players dead)
		start countdown at 10s
		while (countdown is not done)
			if (user input)
				goto: levelUpdate
		goto: leaderboard

	else if (boss dead)
		fade out
		goto: missions

missions:
	start cutscene
	while (cutscene is not done)

	if (levelsDone is less than 7)
		goto: level
	else
		goto: end


leaderboard:
	while (no user input)
		display scores
	goto: start

end:
	start cutscene
	while (cutscene not done)

	goto: start
*/