#include "Level.h"
#include <fstream>
#include <string>

Level::Level()
{
	font.loadFromFile("res/aero-fighters.ttf");
}

Level::~Level()
{
	while (objects.size() > 0)
	{
		delete objects[objects.size() - 1];
		objects.erase(objects.end() - 1);
	}
}

void Level::load(sf::Vector2u winSize, short country, int mapId)
{
	this->country = country;
	this->winSize = winSize;

	ui.setFont(font);
	ui.setPosition(0, 0);

	backgroundImg.loadFromFile("Res/England/England.png");
	frontbackgroundImg.loadFromFile("Res/England/FrontEngland.png");

	background.setSize(sf::Vector2f(winSize));
	frontbackground.setSize(sf::Vector2f(winSize));
	backgroundDist = backgroundImg.getSize().y - winSize.y;
	rect = sf::IntRect(0, backgroundDist, winSize.x, winSize.y);
	frontRect = rect;
	background.setTexture(&backgroundImg);
	frontbackground.setTexture(&frontbackgroundImg);
	background.setTextureRect(rect);
	frontbackground.setTextureRect(rect);
	frontbackgroundImg.setRepeated(true);
	frontbackgroundDist = winSize.y;
	frontbackground.setPosition(0, frontbackgroundDist);
	

	playerImg.loadFromFile("Res/Misc/players.png");
	projectileImg.loadFromFile("Res/Misc/Projectiles.png");
	powerUpImg.loadFromFile("Res/Misc/Powerups.png");
	moneyImg.loadFromFile("Res/Misc/money.png");
	explosionImg.loadFromFile("Res/Misc/Explosion.png");
	enemyImg.loadFromFile("Res/Misc/enemies.png");
	enemyProjectileImg.loadFromFile("Res/Misc/Enemy projectiles.png");
	houseImg.loadFromFile("Res/England/House.png");
	domeImg.loadFromFile("Res/England/Dome.png");
	gateImg.loadFromFile("Res/England/Gate.png");
	hoodImg.loadFromFile("Res/England/Hood.png");
	coneImg.loadFromFile("Res/England/Cone.png");
	roofusImg.loadFromFile("Res/England/Roofus.png");
	domeAnimationImg.loadFromFile("Res/England/Dome animation.png");
	missileImg.loadFromFile("Res/Misc/missles.png");
	avroBomberImg.loadFromFile("Res/England/Avro Bomber.png");

	p[0] = new Player(country, true, &backgroundSpeed);
	p[1] = new Player(country, false, &backgroundSpeed);
	objects.push_back(p[0]);
	objects.push_back(p[1]);

	// Change later. This just spaces out the players
	objects.at(0)->setPos(sf::Vector2f(winSize.x * 0.25f, winSize.y * 0.75f));
	objects.at(1)->setPos(sf::Vector2f(winSize.x * 0.75f, winSize.y * 0.75f));

	// just a test to try out the moved animator to object
	objects.at(0)->setTexture(&playerImg, sf::Vector2i(32, 32), sf::Vector2i(0, 16), 5, false);
	objects.at(1)->setTexture(&playerImg, sf::Vector2i(32, 32), sf::Vector2i(0, 16), 5, false);

	objects.push_back(new Air(0, true, &backgroundDist, 0, winSize, &objects, sf::Vector2f(winSize.x * 0.5f,
	winSize.y * 0.5f), sf::Vector2f(0, 0)));

	short type, id;
	int startMark;
	sf::Vector2f pos, vel;

	std::fstream file;

	file.open("Res/England/enemies.txt");

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
			
			objects.push_back(new Land(id, true, &backgroundSpeed, winSize, &objects, pos, vel));
			break;
		case 1: //air 
			file >> startMark;
			objects.push_back(new Air(id, true, &backgroundDist, startMark, winSize, &objects, pos, vel));
			break;
		case 2:
			break;
		}

	}
}

//You need to set spriteNum to change the texture.
void Level::initializeTextures(int index)
{
	sf::IntRect objRect;
	int frameCount = 0;
	sf::Texture* texPtr = nullptr;

	Object* object = objects[objects.size() - 1 - index];

	if (!object->isTexInit())
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

	if (texPtr)
		object->setTexture(texPtr, objRect.getSize(),
			objRect.getPosition(), frameCount, false);
}

void Level::initTexturesBoss(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &avroBomberImg;
	frameCount = 1;
	switch (object->getID())
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

void Level::initTexturesLand(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &enemyImg;
	frameCount = 1;
	orient = object->getOrientation();
	short spriteNum = object->getSpriteNum();
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

void Level::initTexturesExplosion(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
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

void Level::initTexturesAir(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &enemyImg;
	frameCount = 1;
	short spriteNum = object->getSpriteNum();
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

void Level::initTexturesProjectile(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
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
		objRect = { 0, 34, 12, 12 };
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

void Level::initTexturesCollectable(Object* object, sf::IntRect& objRect, int& frameCount, sf::Texture*& texPtr)
{
	texPtr = &powerUpImg;
	frameCount = 8;
	switch (object->getID())
	{
	case 0:
		objRect = { country * 22, 0, 11, 12 };
		texPtr = &moneyImg;
		frameCount = 2;
		break;
	case 1:
	case 2:
	case 3:
		objRect = { 0, 0 + 20 * (object->getID() - 1), 16, 19 };
		break;
	}
}

bool Level::update(sf::Vector2u winSize)
{
	std::string s = "P1 Lives: " + std::to_string(p[0]->getHealth()) + "\nP2 Lives: " 
	+ std::to_string(p[1]->getHealth()) + "\nP1 Bombs: " + std::to_string(p[0]->getSpecialCharge()) 
	+ "\nP2 Bombs: " + std::to_string(p[1]->getSpecialCharge());
	ui.setString(s);
	ui.setCharacterSize(12);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && infScrollInPos)
		setInfScroll(false);

	// The background has to scroll backwards to get the effect that we want.
	if (!infScrollInPos || !infScrollEnabled)
	{
		backgroundDist -= backgroundSpeed;
		rect.top = backgroundDist;
		background.setTextureRect(rect);
	}
	updateInfScroll();

	// for smoothing out background. 
	// I offset the the background by negative decapitating the background float. 
	// SFML will smooth out not pixel aligned things.
	background.setPosition(0, float(int(backgroundDist) - backgroundDist));
	
	getInput(winSize);

	// checking the back of the vector first is needed,
	// so deleting doesn't shift everything down and mess up the for loop
	// delete first, then erase

	//polymorphism -- All objects are stored in this vector, they can be
	//identified using getType()
	for (int i = 0; i < objects.size(); i++)
	{
		initializeTextures(i);
		objects[objects.size() - 1 - i]->update(winSize, &objects, p[1]->getTime());
		initializeTextures(i);
	}

	for (int i = 0; i < objects.size(); i++)
		if (objects[objects.size() - 1 - i]->shouldDelete())
		{
			delete objects[objects.size() - 1 - i];
			objects.erase(objects.end() - 1 - i);
		}

	englandUpdate(winSize);

	return p[0]->getHealth() > 0 || p[1]->getHealth() > 0;
}

void Level::setInfScroll(bool enable)
{
	infScrollEnabled = enable;
	infScrollInPos = false;

	if (enable)
	{
		frontRect.top = 0;
		frontbackground.setTextureRect(rect);
		frontbackgroundDist = -int(winSize.y);
		frontbackground.setPosition(0, frontbackgroundDist);
	}
}

void Level::updateInfScroll()
{
	if (infScrollEnabled || !infScrollInPos)
	{
		if (infScrollInPos)
		{
			frontRect.top -= backgroundSpeed;
			frontbackground.setTextureRect(frontRect);
		}
		else
		{
			frontbackgroundDist += backgroundSpeed;
			frontbackground.setPosition(0, frontbackgroundDist);
		}

		if ((frontbackgroundDist == winSize.y || frontbackgroundDist == 0) && !infScrollInPos)
			infScrollInPos = true;
	}
}

void Level::statesUpdate(sf::Vector2u winSize)
{
	if (backgroundDist == 0 && !infScrollEnabled)
		setInfScroll(true);
	return;
}

void Level::japanUpdate(sf::Vector2u winSize)
{
	if (!(p[1]->getTime()))
		backgroundSpeed = 0;
	if (backgroundDist == 0 && !infScrollEnabled)
		setInfScroll(true);
	else
		backgroundSpeed = 1;
}

void Level::swedenUpdate(sf::Vector2u winSize)
{
	if (backgroundDist <= 0)
		backgroundSpeed = 0;
	return;
}

void Level::englandUpdate(sf::Vector2u winSize)
{
	if (backgroundDist == 0 && !infScrollEnabled)
	{
		setInfScroll(true);
		if (bossSpawned == false)
		{
			objects.push_back(new Boss(0, true, sf::Vector2f(winSize.x / 2, 
			0), sf::Vector2f(0, 20), &objects));
			backgroundSpeed = 3;
			bossSpawned = true;
		}
	}
	//Slow down for fort
	else if (backgroundDist <= 1405 && backgroundDist > 1264)
		backgroundSpeed = 0.5;
	else
		backgroundSpeed = 1;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(frontbackground, states);
	
	// Drawing priority
	// Slightly cleaner than what was here
	// Explosions and projectiles first
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->isTexInit())
			switch (objects.at(i)->getType())
			{
			case Object::LAND:
				target.draw(*objects[i]);
			}
	}

	for (int i = objects.size() - 1; i >= 0; i--)
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
	
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->isTexInit())
			switch (objects[i]->getType())
			{
			case Object::ENEMY_PROJECTILE:
			case Object::EXPLOSION:
			case Object::PLAYER_PROJECTILE:
				target.draw(*objects[i]);
			}
	}

	target.draw(ui, states);
}

void Level::getInput(sf::Vector2u winSize)
{
	// controller controls
	// works with 2 controllers
	sf::Vector2f move;
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
			move.x = key(i, Controls::Right) - key(i, Controls::Left);
			move.y = key(i, Controls::Back) - key(i, Controls::Forward);

			shoot = key(i, Controls::Shoot);
			special = key(i, Controls::Special);

			spawn = key(i, Controls::Spawn);
		}

		objects.at(i)->setVel(move * 5.f);
		if (shoot)
		{
			if (shoot && !playerShootLast[i])
				p[i]->shoot(objects);
			playerShootLast[i] = true;
		}
		else
			playerShootLast[i] = false;

		if (special)
			p[i]->special(objects, winSize);

		//if (spawn) //Temporary and should be changed to continue.
		//{
		//	p[0]->setHealth(3);
		//	p[1]->setHealth(3);
		//}
	}
}
