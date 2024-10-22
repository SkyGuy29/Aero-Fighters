#include "Level.h"
#include <fstream>
#include <string>


Level::Level(sf::RenderWindow& window) :
	window(window)
{
	font.loadFromFile("res/aero-fighters.ttf");
}


Level::~Level()
{
	EntityManagementInterface::unload();
}


sf::View Level::view;


void Level::setView(sf::View new_view)
{
	view = new_view;
}


float Level::getBackgroundSpeed() const
{
	return backgroundSpeed;
}


/// <summary>
/// Initializes the level with the given country and map.
/// </summary>
/// <param name="winSize"></param>
/// <param name="country"></param>
/// <param name="map"></param>
/// <param name="levelEditor">Whether or not the levelEditor is active.</param>
void Level::load(sf::Vector2f winSize, const short country,
	const Map map, const bool levelEditor)
{
	this->country = country;
	this->winSize = winSize;
	levelEditorActive = levelEditor;
	Entity::setCurrentTick(currentTick);

	// setting up the background
	backgroundImg.loadFromFile("res/"  + mapStrings[map] + "/" + mapStrings[map] + ".png");
	if(map == England)
		frontbackgroundImg.loadFromFile("res/"  + mapStrings[map] + "/Front"  + mapStrings[map] + ".png");

	background.setSize(sf::Vector2f(backgroundImg.getSize()));
	background.setPosition(0, 0 - 2240 + winSize.y);
	
	bossBackground.setSize(sf::Vector2f(winSize));
	bossBackground.setPosition(0, 0 - 2240 + 320);
	backgroundDist = (float)backgroundImg.getSize().y - winSize.y;
	//rect = sf::IntRect(0, (int)backgroundDist, (int)winSize.x, (int)winSize.y);
	//frontRect = rect;
	background.setTexture(&backgroundImg);
	bossBackground.setTexture(&bossBackgroundImg);
	//background.setTextureRect(rect);
	//frontbackground.setTextureRect(rect);
	bossBackgroundImg.setRepeated(true);
	bossBackground.setPosition(0, 0);

	// loading resources
	/*playerImg.loadFromFile("res/Misc/players.png");
	projectileImg.loadFromFile("res/Misc/Projectiles.png");
	powerUpImg.loadFromFile("res/Misc/Powerups.png");
	moneyImg.loadFromFile("res/Misc/money.png");
	explosionImg.loadFromFile("res/Misc/Explosion.png");
	enemyImg.loadFromFile("res/Misc/enemies.png");
	enemyProjectileImg.loadFromFile("res/Misc/Enemy projectiles.png");
	missileImg.loadFromFile("res/Misc/missles.png");*/

	// Seperate player texture for drawing lives
	playerImgRepeat = playerImg;
	playerImgRepeat.setRepeated(true);

	p1Score.setFont(font);
	p2Score.setFont(font);
	p1LivesRect.setTexture(&playerImgRepeat);
	p2LivesRect.setTexture(&playerImgRepeat);
	p1LivesRect.setTextureRect(sf::IntRect(0, 16, 32, 32));
	p2LivesRect.setTextureRect(sf::IntRect(0, 16, 32, 32));
	p1Score.setCharacterSize(16);
	p2Score.setCharacterSize(16);

	switch (map)
	{
	case Map::England:
			houseImg.loadFromFile("res/England/House.png");
			domeImg.loadFromFile("res/England/Dome.png");
			gateImg.loadFromFile("res/England/Gate.png");
			hoodImg.loadFromFile("res/England/Hood.png");
			coneImg.loadFromFile("res/England/Cone.png");
			roofusImg.loadFromFile("res/England/Roofus.png");
			domeAnimationImg.loadFromFile("res/England/Dome animation.png");
			avroBomberImg.loadFromFile("res/England/Avro Bomber.png");
			break;
	}

	EntityManagementInterface::load(map);

	// just a test to try out the moved animator to object
	/*objects.at(0)->setTexture(&playerImg, sf::Vector2i(32, 32),
		sf::Vector2i(0, 16), 5, false);
	objects.at(1)->setTexture(&playerImg, sf::Vector2i(32, 32), 
		sf::Vector2i(0, 16), 5, false);*/

	// ?
	/*objects.push_back(new Air(0, true, &backgroundDist, 0, winSize,
		&objects, sf::Vector2f(winSize.x * 0.5f,
	winSize.y * 0.5f), sf::Vector2f(0, 0), levelEditor));*/

	/*
		The enemy knows where it is at all times.
		It knows this because it knows where it isn't.
		By subtracting where it is from where it isn't,
		or where it isn't from where it is (whichever is greater),
		it obtains a difference, or deviation.
		The guidance subsystem uses deviations to generate
		corrective commands to drive the missile from a position
		where it is to a position where it isn't,
		and arriving at a position where it wasn't, it now is.
		Consequently, the position where it is,
		is now the position that it wasn't,
		and it follows that the position that it was,
		is now the position that it isn't.
		In the event that the position that it is in is not
		the position that it wasn't, the system has acquired a variation,
		the variation being the difference between where the enemy is,
		and where it wasn't.
		If variation is considered to be a significant factor,
		it too may be corrected by the GEA.
		However, the enemy must also know where it was.
		The enemy guidance computer scenario works as follows.
		Because a variation has modified some of the information
		the enemy has obtained, it is not sure just where it is.
		However, it is sure where it isn't, within reason,
		and it knows where it was.
		It now subtracts where it should be from where it wasn't,
		or vice-versa, and by differentiating this from the
		algebraic sum of where it shouldn't be, and where it was,
		it is able to obtain the deviation and its variation,
		which is called error.
	*/
}


/// <summary>
/// Enables debug mode. Gives both players infinite health.
/// </summary>
void Level::debugMode() const
{
	EntityManagementInterface::getPlayers()[0]->setHealth(HP_MAX);
	EntityManagementInterface::getPlayers()[1]->setHealth(HP_MAX);
}

int Level::skipToBoss()
{
	int offset = 200;
	backgroundDist = -offset;
	return offset-backgroundImg.getSize().y;
}

void Level::respawnPlayers() const
{
	EntityManagementInterface::getPlayers()[0]->setHealth(3);
	EntityManagementInterface::getPlayers()[1]->setHealth(3);
}


/// <summary>
/// Updates the level.
/// </summary>
/// <param name="winSize"></param>
/// <returns></returns>
bool Level::update(const sf::Vector2f winSize)
{
	// Just for debugging
	// The bug where holding enter freezes the background, 
	// but not the enemies is caused by this
	// We don't really need this anymore anyways
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && infScrollInPos)
		//setInfScroll(false);

	if(levelEditorActive)
		updateLevelEditor();

	// The background has to scroll backwards to get the effect that we want.
	if (!bossBackgroundSet)
		backgroundDist -= backgroundSpeed;
	else
		bossBackground.setTextureRect(sf::IntRect(
			0, view.getCenter().y - winSize.y / 2.f, winSize.x, winSize.y));

	// There was a gap, 7 worked perfect on the 5th try
	// There is still some weird jumpyness when: 
	//		the boss background is first shown, but it fixes itself,
	//		fastforwarding moves the boss background down to a third of the screen.
	// Doesn't speed up yet, only uses view instead of backgroundSpeed,
	// I just wanted to get this sort of working. - Ben
	bossBackground.setPosition(0, view.getCenter().y - winSize.y / 2.f);

	// for smoothing out background. 
	// Take the decimal, leave the whole number
	// SFML will smooth out not pixel aligned things.
	//background.setPosition(0, 0-backgroundImg.getSize().y - backgroundDist);

	// Drawing order
	EntityManagementInterface::tick(window, currentTick);
	
	/*updatePlayers();
	p[0]->updateBgSpeed(&backgroundSpeed);
	p[1]->updateBgSpeed(&backgroundSpeed);
	*/

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop
	// delete first, then erase

	englandUpdate();

	// Update scores and stuff after update,
	// so the game over screen doesn't freeze it with one life left
	p1Score.setString(std::to_string(player1Score));
	p2Score.setString(std::to_string(player2Score));

	p1LivesRect.setSize(sf::Vector2f(16.f * p[0]->getHealth(), 16));
	p2LivesRect.setSize(sf::Vector2f(16.f * p[1]->getHealth(), 16));
	p1LivesRect.setTextureRect(sf::IntRect(0, 16, 32 * p[0]->getHealth(), 32));
	p2LivesRect.setTextureRect(sf::IntRect(0, 16, 32 * p[1]->getHealth(), 32));
	p1LivesRect.setPosition(sf::Vector2f(0, view.getCenter().y - view.getSize().y / 2.f));
	p2LivesRect.setPosition(sf::Vector2f(view.getCenter().x + view.getSize().x / 2.f - p2LivesRect.getLocalBounds().width, view.getCenter().y - view.getSize().y / 2.f));

	// Place scores in middle top
	// Scores were not implemented, so these values never change for now
	p1Score.setPosition(sf::Vector2f(winSize.x / 2 - 20 - p1Score.getLocalBounds().width,
		view.getCenter().y - view.getSize().y / 2.f -p1Score.getLocalBounds().height ));
	p2Score.setPosition(sf::Vector2f(winSize.x / 2 + 20,
		view.getCenter().y - view.getSize().y / 2.f -p2Score.getLocalBounds().height));

	window.draw(p1Score);
	window.draw(p2Score);

	window.draw(p1LivesRect);
	window.draw(p2LivesRect);

	if (!levelEditorActive)
		currentTick++;

	return p[0]->getHealth() > 0 || p[1]->getHealth() > 0;
}

void Level::updateLevelEditor()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		{
			backgroundSpeed = 25;
			while (currentTick <= currentTick + 25)
			{
				currentTick++;
				EntityManagementInterface::tick(window, currentTick);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
		{
			backgroundSpeed = -25;
			while (currentTick >= currentTick - 25)
			{
				currentTick--;
				EntityManagementInterface::tick(window, currentTick);
			}
		}
	}
}


void Level::statesUpdate()
{
	if (backgroundDist == 0 && !bossBackgroundSet)
		bossBackgroundSet = true;
}


void Level::japanUpdate()
{
	if (!(p[1]->getTime()))
		backgroundSpeed = 0;
	if (backgroundDist == 0 && !bossBackgroundSet)
		bossBackgroundSet = true;
	else
		backgroundSpeed = 1;
}


void Level::swedenUpdate()
{
	if (backgroundDist <= 0)
		backgroundSpeed = 0;
	return;
}


void Level::englandUpdate()
{
	if (backgroundDist <= 0 && !levelEditor && !bossBackgroundSet)
	{
		bossBackgroundSet = true;
		if (bossSpawned == false)
		{
			entities.bossEnemies.push_back(Enemy_new(sf::Vector2f(winSize.x / 2,
				-150), sf::Vector2f(0, 5), EntityID::BOSS_ENGLAND));
			bossSpawned = true;
		}
	}
	//Slow down for fort
	else if (backgroundDist <= 1405 && backgroundDist > 1264)
		backgroundSpeed = 0.5;
	else if (!bossBackgroundSet)
		backgroundSpeed = 1;
	// We are using viewport now, needs to change view scroll speed.
	else if (bossBackgroundSet && backgroundSpeed < 7)
		backgroundSpeed *= 1.01f;
}