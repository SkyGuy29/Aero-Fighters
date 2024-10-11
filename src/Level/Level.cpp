#include "Level.h"
#include <fstream>
#include <string>

bool Level::levelEditor = false;

Level::Level(sf::RenderWindow& window) :
	window(window)
{
	font.loadFromFile("res/aero-fighters.ttf");
}


Level::~Level()
{
	deleteVector((std::vector<void*>&)entities.landEnemies);
	deleteVector((std::vector<void*>&)entities.airEnemies);
	deleteVector((std::vector<void*>&)entities.waterEnemies);
	deleteVector((std::vector<void*>&)entities.bossEnemies);
	deleteVector((std::vector<void*>&)entities.players);
	deleteVector((std::vector<void*>&)entities.projectiles);
	deleteVector((std::vector<void*>&)entities.permanentSpawners);
	deleteVector((std::vector<void*>&)entities.temporarySpawners);
	deleteVector((std::vector<void*>&)entities.tileEntities);
	deleteVector((std::vector<void*>&)entities.powerUps);

}


void Level::setView(sf::View new_view)
{
	view = new_view;
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
	this->levelEditor = levelEditor;

	// setting up the background
	backgroundImg.loadFromFile("res/"  + mapStrings[map] + "/" + mapStrings[map] + ".png");
	if(map == England)
		frontbackgroundImg.loadFromFile("res/"  + mapStrings[map] + "/Front"  + mapStrings[map] + ".png");

	background.setSize(sf::Vector2f(backgroundImg.getSize()));
	background.setPosition(0, 0 - 2240 + winSize.y);
	
	frontbackground.setSize(sf::Vector2f(winSize));
	frontbackground.setPosition(0, 0 - 2240 + 320);
	backgroundDist = (float)backgroundImg.getSize().y - winSize.y;
	//rect = sf::IntRect(0, (int)backgroundDist, (int)winSize.x, (int)winSize.y);
	//frontRect = rect;
	background.setTexture(&backgroundImg);
	frontbackground.setTexture(&frontbackgroundImg);
	//background.setTextureRect(rect);
	//frontbackground.setTextureRect(rect);
	frontbackgroundImg.setRepeated(true);
	frontbackgroundDist = winSize.y;
	frontbackground.setPosition(0, frontbackgroundDist);

	// loading resources
	playerImg.loadFromFile("res/Misc/players.png");
	projectileImg.loadFromFile("res/Misc/Projectiles.png");
	powerUpImg.loadFromFile("res/Misc/Powerups.png");
	moneyImg.loadFromFile("res/Misc/money.png");
	explosionImg.loadFromFile("res/Misc/Explosion.png");
	enemyImg.loadFromFile("res/Misc/enemies.png");
	enemyProjectileImg.loadFromFile("res/Misc/Enemy projectiles.png");
	missileImg.loadFromFile("res/Misc/missles.png");

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
		case England:
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

	entities.players.push_back(new Player_new(sf::Vector2(0,0), sf::Vector2f(0,0), EntityID::PLAYER, backgroundSpeed, country, true, &backgroundSpeed));
	entities.players.push_back(new Player_new(country, false, &backgroundSpeed));

	// Change later. This just spaces out the players
	entities.players[0]->getSprite()->setPosition(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	entities.players[1]->getSprite()->setPosition(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	/*objects.at(0)->setTexture(&playerImg, sf::Vector2i(32, 32),
		sf::Vector2i(0, 16), 5, false);
	objects.at(1)->setTexture(&playerImg, sf::Vector2i(32, 32), 
		sf::Vector2i(0, 16), 5, false);*/

	// ?
	/*objects.push_back(new Air(0, true, &backgroundDist, 0, winSize,
		&objects, sf::Vector2f(winSize.x * 0.5f,
	winSize.y * 0.5f), sf::Vector2f(0, 0), levelEditor));*/
}


/// <summary>
/// Enables debug mode. Gives both players infinite health.
/// </summary>
void Level::debugMode() const
{
	Player_new::getPlayers()[0]->setHealth(HP_MAX);
	Player_new::getPlayers()[1]->setHealth(HP_MAX);
}

void Level::respawnPlayers() const
{
	Player_new::getPlayers()[0]->setHealth(3);
	Player_new::getPlayers()[1]->setHealth(3);
}


/// <summary>
/// Initializes textures of objects in the object list based on the provided index. You need to set spriteNum to change the texture.
/// </summary>
/// <param name="index"></param>
void Level::initializeTextures(const int index)
{
	sf::IntRect objRect;
	int frameCount = 0;
	sf::Texture* texPtr = nullptr;

	Entity* entity = entities[entities.size() - 1 - index];

	// if the texture is not initialized
	if (!object->isTexInit())
	{
		switch (object->getType())
		{
		case Object::BOSS:
			initTexturesBoss(object, objRect, frameCount, texPtr);
			break;
		case Object::LAND:
			initTexturesLand(object, objRect, frameCount, texPtr);
			break;
		case Object::EXPLOSION:
			initTexturesExplosion(object, objRect, frameCount, texPtr);
			break;
		case Object::AIR:
			initTexturesAir(object, objRect, frameCount, texPtr);
			break;
		case Object::PLAYER_PROJECTILE:
		case Object::ENEMY_PROJECTILE:
			initTexturesProjectile(object, objRect, frameCount, texPtr);
			break;
		case Object::COLLECTABLE:
			initTexturesCollectable(object, objRect, frameCount, texPtr);
		}
	}

	if (texPtr)
		object->setTexture(texPtr, objRect.getSize(),
			objRect.getPosition(), frameCount, false);
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

	if(levelEditor)
		updateLevelEditor();

	// The background has to scroll backwards to get the effect that we want.
	if (infScrollInPos || infScrollEnabled)
	{
		backgroundDist -= backgroundSpeed;
	
	}

	updateInfScroll();

	// for smoothing out background. 
	// Take the decimal, leave the whole number
	// SFML will smooth out not pixel aligned things.
	//background.setPosition(0, 0-backgroundImg.getSize().y - backgroundDist);
	
	updatePlayers();

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop
	// delete first, then erase

	//polymorphism -- All objects are stored in this vector, they can be
	//identified using getType()
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[entities.size() - 1 - i]->tick(
			Player_new::getPlayers()[1]->getTime() && player1Score, player2Score);
		/*if (objects[objects.size() - 1 - i]->getType() == Object::EXPLOSION)
		{
			// I'm sorry.
			// Explosions didn't move before. They move now
			// I didn't want to add more polymorphism stuff
			// Pointers are cool
			Explosion* exp = (Explosion*)objects[objects.size() - 1 - i];
			exp->backgroundSpeed = backgroundSpeed;
		}*/
	}

	// Calling init textures after everything is updated.
	// Objects may create explosions that won't be drawn, 
	// because the loop won't reach them
	//for (unsigned int i = 0; i < entities.size(); i++)
	//	initializeTextures(i); // ?? - Andrew 9/16/24
	
	// Drawing order
	generalTick((std::vector<Entity*>&)entities.landEnemies);
	generalTick((std::vector<Entity*>&)entities.tileEntities);
	generalTick((std::vector<Entity*>&)entities.waterEnemies);

	generalTick((std::vector<Entity*>&)entities.powerUps);
	generalTick((std::vector<Entity*>&)entities.players);
	generalTick((std::vector<Entity*>&)entities.projectiles);
	
	generalTick((std::vector<Entity*>&)entities.bossEnemies);
	generalTick((std::vector<Entity*>&)entities.airEnemies);

	generalTick((std::vector<Entity*>&)entities.permanentSpawners);
	generalTick((std::vector<Entity*>&)entities.temporarySpawners);

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
		view.getCenter().y - view.getSize().y / 2.f -p2Score.getLocalBounds().height ));
	p2Score.setPosition(sf::Vector2f(winSize.x / 2 + 20,
		view.getCenter().y - view.getSize().y / 2.f -p2Score.getLocalBounds().height));

	window.draw(p1Score);
	window.draw(p2Score);

	window.draw(p1LivesRect);
	window.draw(p2LivesRect);

	return p[0]->getHealth() > 0 || p[1]->getHealth() > 0;
}


/// <summary>
/// Changes whether we should scroll or not.
/// </summary>
/// <param name="enable"></param>
void Level::setInfScroll(const bool enable)
{
	infScrollEnabled = enable;
	infScrollInPos = false;

	if (enable)
	{
		//frontRect.top = 0;
		//frontbackground.setTextureRect(rect);
		frontbackgroundDist = (float) -(int)winSize.y;
		frontbackground.setPosition(0, frontbackgroundDist);
	}
}


/// <summary>
/// Updates the background based on if we're scrolling or not.
/// </summary>
void Level::updateInfScroll()
{
	if (!(infScrollEnabled || !infScrollInPos))
		return;

	if (infScrollInPos)
	{
		//frontRect.top -= (int)backgroundSpeed;
		//frontbackground.setTextureRect(frontRect);
	}
	else
	{
		frontbackgroundDist += backgroundSpeed;
		frontbackground.setPosition(0, frontbackgroundDist);
	}

	if ((frontbackgroundDist == winSize.y || frontbackgroundDist >= 0) 
		&& !infScrollInPos)
		infScrollInPos = true;
}


void Level::updateLevelEditor()
{
	setInfScroll(false);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
			backgroundSpeed = 25;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
			backgroundSpeed = -25;
		backgroundDist -= backgroundSpeed;
		//rect.top = (int)backgroundDist;
		//background.setTextureRect(rect);
	}
}


void Level::deleteVector(std::vector<void*>& a)
{
	for (int i = 0; i < a.size(); i++)
		delete a[i];
	a.clear();
}


/// <summary>
/// Controls the players.
/// </summary>
void Level::updatePlayers()
{
	// controller controls
	// works with 2 controllers

	// Move Offset
	sf::Vector2f move;

	// If the player should shoot
	bool shoot, special;
	bool spawn;

	for (int i = 0; i < 2; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			move = joystick(i);

			shoot = button(i, Controller::Y);
			special = button(i, Controller::B);

			spawn = button(i, Controller::A);
		}
		else
		{
			move.x = (float)key(i, Controls::Right) - key(i, Controls::Left);
			move.y = (float)key(i, Controls::Back) - key(i, Controls::Forward);

			shoot = key(i, Controls::Shoot);
			special = key(i, Controls::Special);

			spawn = key(i, Controls::Spawn);
		}

		entities.players.at(i)->setVel(move * 5.f);
		if (shoot)
		{
			if (!playerShootLast[i])
				entities.players[i]->shoot(objects);
			playerShootLast[i] = true;
		}
		else
			playerShootLast[i] = false;

		if (special)
			entities.players[i]->special(objects, winSize);

		if (spawn) //Temporary and should be changed to continue.
		{
			entities.players[0]->setHealth(3);
			entities.players[1]->setHealth(3);
		}
	}
}


void Level::statesUpdate()
{
	if (backgroundDist == 0 && !infScrollEnabled)
		setInfScroll(true);
}


void Level::japanUpdate()
{
	if (!(p[1]->getTime()))
		backgroundSpeed = 0;
	if (backgroundDist == 0 && !infScrollEnabled)
		setInfScroll(true);
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
	if (backgroundDist <= 0 && !levelEditor && !infScrollEnabled)
	{
		setInfScroll(true);
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
	else if (!infScrollEnabled)
		backgroundSpeed = 1;
	else if (infScrollEnabled && backgroundSpeed < 7)
		backgroundSpeed *= 1.01f;
}