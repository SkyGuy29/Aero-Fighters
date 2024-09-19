#include "Level.h"
#include <fstream>
#include <string>


Level::Level()
{
	font.loadFromFile("res/aero-fighters.ttf");
}


Level::~Level()
{
	while (!objects.empty())
	{
		delete objects[objects.size() - 1];
		objects.erase(objects.end() - 1);
	}
}


sf::View Level::view;


void Level::setView(sf::View new_view)
{
	view = new_view;
}


float Level::getBackgroundSpeed()
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

	p[0] = new Player(country, true, &backgroundSpeed);
	p[1] = new Player(country, false, &backgroundSpeed);
	objects.push_back(p[0]);
	objects.push_back(p[1]);

	// Change later. This just spaces out the players
	objects.at(0)->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	objects.at(1)->setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	objects.at(0)->setTexture(&playerImg, sf::Vector2i(32, 32), 
		sf::Vector2i(0, 16), 5, false);
	objects.at(1)->setTexture(&playerImg, sf::Vector2i(32, 32), 
		sf::Vector2i(0, 16), 5, false);

	// ?
	objects.push_back(new Air(0, true, &backgroundDist, 0, winSize, 
		&objects, sf::Vector2f(winSize.x * 0.5f,
	winSize.y * 0.5f), sf::Vector2f(0, 0), levelEditor));

	short type, id;
	int startMark;
	sf::Vector2f pos, vel;
	std::fstream file;

	file.open("res/" + mapStrings[map] + "/enemies.txt");

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

	// loading the enemies
	while (file.is_open() && !file.eof())
	{
		file >> type;
		file >> id;
		file >> pos.x;
		file >> pos.y;
		file >> vel.x;
		file >> vel.y;

		switch (type)
		{
		case 0: //land
			objects.push_back(new Land(id, true, &backgroundSpeed,
				&objects, pos, vel, levelEditor));
			break;
		case 1: //air 
			file >> startMark;
			objects.push_back(new Air(id, true, &backgroundDist, startMark, 
				winSize, &objects, pos, vel, levelEditor));
			break;
		case 2:
			break;
		}
	}
	//I am so sorry -Gabe
}


/// <summary>
/// Enables debug mode. Gives both players infinite health.
/// </summary>
void Level::debugMode() const
{
	p[0]->setHealth(HP_MAX);
	p[1]->setHealth(HP_MAX);
}

void Level::respawnPlayers() const
{
	p[0]->setHealth(3);
	p[1]->setHealth(3);
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

	Object* object = objects[objects.size() - 1 - index];

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

	// Debugging death screen kill players
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		p[0]->setHealth(0);
		p[1]->setHealth(0);
	}

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
	p[0]->updateBgSpeed(&backgroundSpeed);
	p[1]->updateBgSpeed(&backgroundSpeed);
	

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop
	// delete first, then erase

	//polymorphism -- All objects are stored in this vector, they can be
	//identified using getType()
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[objects.size() - 1 - i]->update(winSize, &objects,
			p[1]->getTime() && !levelEditor, player1Score, player2Score);
		if (objects[objects.size() - 1 - i]->getType() == Object::EXPLOSION)
		{
			// I'm sorry.
			// Explosions didn't move before. They move now
			// I didn't want to add more polymorphism stuff
			// Pointers are cool
			Explosion* exp = (Explosion*)objects[objects.size() - 1 - i];
			exp->backgroundSpeed = backgroundSpeed;
		}
	}

	// Calling init textures after everything is updated.
	// Objects may create explosions that won't be drawn, 
	// because the loop won't reach them
	for (unsigned int i = 0; i < objects.size(); i++)
		initializeTextures(i);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		// logic after && symbol is for when the level editor is active we dont want to remove enemies when offscreen
		if (objects[objects.size() - 1 - i]->shouldDelete() &&
			(!(objects[objects.size() - 1 - i]->getType() == Object::LAND ||
			objects[objects.size() - 1 - i]->getType() == Object::AIR) || !levelEditor))
		{
			delete objects[objects.size() - 1 - i];
			objects.erase(objects.end() - 1 - i);
		}
	}

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

		for (Object* object : objects)
		{
			switch (object->getType())
			{
				case Object::LAND:
					object->setPos(object->getPos().x, object->getPos().y + backgroundSpeed);
			}
		}
	}


}


/// <summary>
/// Draws the level.
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void Level::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(frontbackground, states);
	
	// Drawing priority
	// Slightly cleaner than what was here
	// Explosions and projectiles first

	for (int i = (int)objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->isTexInit())
		{
			switch (objects.at(i)->getType())
			{
			case Object::LAND:
				target.draw(*objects[i]);
			}
		}
	}

	for (int i = (int)objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->isTexInit())
			switch (objects.at(i)->getType())
			{
			case Object::AIR:
			case Object::BOSS_PIECE:
			case Object::COLLECTABLE:
			case Object::PLAYER:
			case Object::BOSS:
				target.draw(*objects[i]);
			}
	}
	
	// Projectiles with a delay think they have a texture to prevent them from 
	// loading their texture early.
	// The draw loop only checked if an object had a texture. 
	// It now also checks if an object has a non-zero width.

	for (int i = (int)objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->isTexInit() && objects[i]->getSize().x > 0)
			switch (objects[i]->getType())
			{
			case Object::ENEMY_PROJECTILE:
			case Object::EXPLOSION:
			case Object::PLAYER_PROJECTILE:
				target.draw(*objects[i]);
			}
	}

	target.draw(p1Score, states);
	target.draw(p2Score, states);

	target.draw(p1LivesRect, states);
	target.draw(p2LivesRect, states);
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

		objects.at(i)->setVel(move * 5.f);
		if (shoot)
		{
			if (!playerShootLast[i])
				p[i]->shoot(objects);
			playerShootLast[i] = true;
		}
		else
			playerShootLast[i] = false;

		if (special)
			p[i]->special(objects, winSize);

		if (spawn) //Temporary and should be changed to continue.
		{
			p[0]->setHealth(3);
			p[1]->setHealth(3);
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
			objects.push_back(new Boss(0, true, sf::Vector2f(winSize.x / 2,
				-150), sf::Vector2f(0, 5), &objects, levelEditor));
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


/// <summary>
/// Initializes a boss texture
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesBoss(Object* object, sf::IntRect& objRect,
	int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &avroBomberImg;
	frameCount = 1;
	switch (object->getId())
	{
	case 0: //Avro Bomber
		objRect = { 8, 4, 164, 150 };
		break;
	case 1: //Avro Bomber Left Wing
		objRect = { 180, 14, 56, 75 };
		break;
	case 2: //Avro Bomber Right Wing
		objRect = { 236, 14, 52, 75 };
		break;
	case 3: //Avro Bomber Middle Part
		objRect = { 288, 14, 56, 75 };
		break;
	}
}


/// <summary>
/// Initializes a land enemy.
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesLand(Object* object, sf::IntRect& objRect,
	int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &enemyImg;
	frameCount = 1;
	orient = object->getOrientation();
	const short spriteNum = object->getSpriteNum();

	switch (spriteNum)
	{
	case 0:	case 1:	case 2:	case 3:	case 4: case 5: // Tanks
		objRect = { 32 * orient, 0 + 40 * (spriteNum - 0), 32, 32 };
		break;
	case 6: case 7: case 8: case 9: case 10:
	case 11: case 12: case 13: case 14: // Boats and Turrets
		objRect = { 32 * orient, 600 + 40 * (spriteNum - 6), 32, 32 };
		break;
	case 15: //Landmines
		objRect = { 520 + 32 * orient, 240, 32, 32 };
		break;
	case 16: //Thing
		objRect = { 520, 280, 32, 32 };
		break;
	case 17: case 18: // Destroyed Boat/Tank
		objRect = { 520 + 32 * orient, (480 + 40 * (spriteNum - 17)), 32, 32 };
		break;
	case 19: //House
		texPtr = &houseImg;
		objRect = { 0, 0, 64, 48 };
		break;
	case 20: //Dome
		texPtr = &domeImg;
		objRect = { 0, 0, 80, 80 };
		break;
	case 21: //Dome Shooty shoot Animation
		texPtr = &houseImg;
		frameCount = 10;
		objRect = { 0, 0, 89, 74 };
		break;
	case 22: //Gate
		texPtr = &gateImg;
		objRect = { 0, 0, 32, 40 };
		break;
	case 23: //Hangar
		texPtr = &hoodImg;
		objRect = { 0, 0, 80, 96 };
		break;
	case 24: //Cone
		texPtr = &coneImg;
		objRect = { 0, 0, 48, 48 };
		break;
	case 25: //Roofus
		texPtr = &roofusImg;
		objRect = { 0, 0, 48, 48 };
		break;
	}
}


/// <summary>
/// Initializes an explosion.
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesExplosion(Object* object, sf::IntRect& objRect,
	int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &explosionImg;
	short spriteNum = object->getSpriteNum();
	switch (spriteNum)
	{
	case 0:
		frameCount = 16;
		objRect = { 0, 0, 48, 48 };
		break;
	case 1:
		frameCount = 11;
		objRect = { 0, 49, 47, 37 };
		break;
	case 2:
		frameCount = 14;
		objRect = { 0, 87, 78, 80 };
		break;
	case 3:
		frameCount = 12;
		objRect = { 0, 168, 38, 41 };
		break;
	}
}


/// <summary>
/// Intializes an air enemy.
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesAir(Object* object, sf::IntRect& objRect,
	int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &enemyImg;
	frameCount = 1;
	const short spriteNum = object->getSpriteNum();

	switch (spriteNum)
	{
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
	case 7: case 8: // Weird things, Regular Copters, and Fighter Jets
		objRect = { 32 * orient, 240 + 40 * (spriteNum - 0), 32, 32 };
		break;
	case 9: //Big Copter Blades
		frameCount = 3;
		objRect = { 520, 0, 64, 64 };
		break;
	case 10: case 11: //Advanced Mega Copter
		objRect = { 520 + 40 * (spriteNum - 10), 64, 32, 96 };
		break;
	case 12: //Big Plane 1
		objRect = { 600, 64, 80, 88 };
		break;
	case 13: //Big Copter 
		objRect = { 688, 64, 48, 72 };
		break;
	case 14: //Big Plane 2
		objRect = { 600, 160, 80, 80 };
		break;
	case 15: case 16: case 17: case 18: //Side & Dive Bombers
		objRect = { 520 + 32 * orient, 320 + 40 * (spriteNum - 15), 32, 32 };
		break;
	case 19: //Regular Copter Blades
		frameCount = 3;
		objRect = { 688, 480, 32, 32 };
		break;
	}
}


/// <summary>
/// Initializes a projectile.
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesProjectile(Object* object, sf::IntRect& objRect,
	int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &projectileImg;
	frameCount = 1;
	orient = object->getOrientation();
	switch (object->getSpriteNum())
	{
	case 0:
		objRect = { (rand() % 3) * 11, 0, 11, 18 };
		break;
	case 1:
		objRect = { (rand() % 3) * 16, 19, 16, 30 };
		break;
	case 2:
		objRect = { (rand() % 3) * 21, 50, 31, 30 };
		break;
	case 3:
		objRect = { (rand() % 3) * 47, 81, 47, 46 };
		break;
	case 4:
		objRect = { (rand() % 3) * 9, 128, 9, 28 };
		break;
	case 5:
		objRect = { (rand() % 3) * 16, 157, 16, 32 };
		break;
	case 6:
		objRect = { (rand() % 3) * 41, 190, 41, 44 };
		break;
	case 7:
		objRect = { (rand() % 3) * 64, 235, 64, 48 };
		break;
	case 8:
		objRect = { (rand() % 3) * 15, 284, 15, 29 };
		break;
	case 9: //Kunai
		objRect = { 0, 314, 9, 31 };
		break;
	case 10:
		objRect = { (rand() % 3) * 9, 346, 9, 31 };
		break;
	case 11:
		objRect = { (rand() % 3) * 16, 378, 16, 31 };
		break;
	case 12: //Enemy Projectile 1
		texPtr = &enemyProjectileImg;
		frameCount = 4;
		objRect = { 0, 0, 8, 8 };
		break;
	case 13: //Breakable
		texPtr = &enemyProjectileImg;
		frameCount = 4;
		objRect = { 0, 8, 14, 14 };
		break;
	case 14: //Breaking
		texPtr = &enemyProjectileImg;
		frameCount = 5;
		objRect = { 0, 22, 16, 12 };
		break;
	case 15: //Big
		texPtr = &enemyProjectileImg;
		frameCount = 2;
		objRect = { 0, 37, 12, 12 };
		break;
	case 16: //Medium
		texPtr = &enemyProjectileImg;
		frameCount = 2;
		objRect = { 0, 46, 10, 10 };
		break;
	case 17: //One pixel projectile
		texPtr = &enemyProjectileImg;
		frameCount = 1;
		objRect = { 0, 56, 4, 4 };
		break;
	case 18: //Missiles 
		/*
		The missile knows where it is at all times.
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
		the variation being the difference between where the missile is,
		and where it wasn't.
		If variation is considered to be a significant factor,
		it too may be corrected by the GEA.
		However, the missile must also know where it was.
		The missile guidance computer scenario works as follows.
		Because a variation has modified some of the information
		the missile has obtained, it is not sure just where it is.
		However, it is sure where it isn't, within reason,
		and it knows where it was.
		It now subtracts where it should be from where it wasn't,
		or vice-versa, and by differentiating this from the
		algebraic sum of where it shouldn't be, and where it was,
		it is able to obtain the deviation and its variation,
		which is called error.
		*/
		switch (orient) //This is so that the flips are correct
		{
		case 8:
			orient = 0;
			break;
		case 7: case 9: case 15:
			orient = 1;
			break;
		case 6: case 10: case 14:
			orient = 2;
			break;
		case 5: case 11: case 13:
			orient = 3;
			break;
		case 12:
			orient = 4;
			break;
		}
		texPtr = &missileImg;
		objRect = { (orient % 5) * 12, 0, 12, 12 };
		break;
	}
}


/// <summary>
/// Initializes a collectable.
/// </summary>
/// <param name="object"></param>
/// <param name="objRect"></param>
/// <param name="frameCount"></param>
/// <param name="texPtr"></param>
void Level::initTexturesCollectable(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &powerUpImg;
	frameCount = 8;
	switch (object->getId())
	{
	case 0:
		objRect = { country * 22, 0, 11, 12 };
		texPtr = &moneyImg;
		frameCount = 2;
		break;
	case 1:
	case 2:
	case 3:
		objRect = { 0, 0 + 20 * (object->getId() - 1), 16, 19 };
		break;
	}
}