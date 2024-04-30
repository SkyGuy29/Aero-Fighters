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

	switch (country)
	{
	case STATES:
		backgroundImg.loadFromFile("Res/States/States.png");
		frontbackgroundImg.loadFromFile("Res/States/FrontStates.png");
		break;
	case JAPAN:
		backgroundImg.loadFromFile("Res/Japan/Japan.png");
		frontbackgroundImg.loadFromFile("Res/Japan/FrontJapan.png");
		break;
	case SWEDEN:
		backgroundImg.loadFromFile("Res/Sweden/Sweden.png");
		break;
	case ENGLAND:
		backgroundImg.loadFromFile("Res/England/England.png");
		frontbackgroundImg.loadFromFile("Res/England/FrontEngland.png");
	}

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

	switch (country)
	{
	case STATES:
		file.open("Res/States/enemies.txt");
		break;
	case JAPAN:
		break;
	case SWEDEN:
		file.open("Res/Sweden/enemies.txt");
		break;
	case ENGLAND:
		file.open("Res/England/enemies.txt");
	}

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
		}
	}
}

//You need to set spriteNum to change the texture.
void Level::initializeTextures(int index)
{
	short moneyOffset = 0;
	orient = objects[objects.size() - 1 - index]->getOrientation();
	if (!objects[objects.size() - 1 - index]->isTexInit())
		switch (objects[objects.size() - 1 - index]->getType())
		{
		case Object::BOSS:
			switch (objects[objects.size() - 1 - index]->getID())
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			}
			break;
		case Object::LAND:
			switch (objects[objects.size() - 1 - index]->getSpriteNum())
			{
			case 0: //Tank 1 base
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 0), 1, false);
				break;
			case 1: //Tank 1a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 40), 1, false);
				break;
			case 2: //Tank 1b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 80), 1, false);
				break;
			case 3: //Tank 2 base
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 120), 1, false);
				break;
			case 4: //Tank 2a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 160), 1, false);
				break;
			case 5: //Tank 2b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 200), 1, false);
				break;
			case 6: //Boat base 1a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 600), 1, false);
				break;
			case 7: //Boat base 1b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 640), 1, false);
				break;
			case 8: //Boat turret 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 680), 1, false);
				break;
			case 9: //Boat base 2a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 720), 1, false);
				break;
			case 10: //Boat base 2b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 760), 1, false);
				break;
			case 11: //Boat turret 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 800), 1, false);
				break;
			case 12: //Turret 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 840), 1, false);
				break;
			case 13: //Turret 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 880), 1, false);
				break;
			case 14: //Turret 3
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 920), 1, false);
				break;
			case 15: //Landmines
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 240), 1, false);
				break;
			case 16: //Thing
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520, 280), 1, false);
				break;
			case 17: //Destroyed Boat/Tank 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 480), 1, false);
				break;
			case 18: //Destroyed Boat/Tank 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 520), 1, false);
				break;
			case 19: //House
				objects[objects.size() - 1 - index]->setTexture(&houseImg,
					sf::Vector2i(64, 48), sf::Vector2i(0, 0), 1, false);
				break;
			case 20: //Dome
				objects[objects.size() - 1 - index]->setTexture(&domeImg,
					sf::Vector2i(80, 80), sf::Vector2i(0, 0), 1, false);
				break;
			case 21: //Dome Shooty shoot Animatio 
				objects[objects.size() - 1 - index]->setTexture(&houseImg,
					sf::Vector2i(89, 74), sf::Vector2i(0, 0), 10, false);
				break;
			case 22: //Gate
				objects[objects.size() - 1 - index]->setTexture(&gateImg,
					sf::Vector2i(32, 40), sf::Vector2i(0, 0), 1, false);
				break;
			case 23: //Hangar
				objects[objects.size() - 1 - index]->setTexture(&hoodImg,
					sf::Vector2i(80, 96), sf::Vector2i(0, 0), 1, false);
				break;
			case 24: //Cone
				objects[objects.size() - 1 - index]->setTexture(&coneImg,
					sf::Vector2i(48, 48), sf::Vector2i(0, 0), 1, false);
				break;
			case 25: //Roofus
				objects[objects.size() - 1 - index]->setTexture(&houseImg,
					sf::Vector2i(48, 48), sf::Vector2i(0, 0), 1, false);
				break;
			}
			break;
		case Object::EXPLOSION:
			switch (objects[objects.size() - 1 - index]->getSpriteNum())
			{
			case 0:
				objects[objects.size() - 1 - index]->setTexture(&explosionImg,
					sf::Vector2i(48, 48), sf::Vector2i(0, 0), 16, false);
				break;
			case 1:
				objects[objects.size() - 1 - index]->setTexture(&explosionImg,
					sf::Vector2i(47, 37), sf::Vector2i(0, 49), 11, false);
				break;
			case 2:
				objects[objects.size() - 1 - index]->setTexture(&explosionImg,
					sf::Vector2i(78, 80), sf::Vector2i(0, 87), 14, false);
				break;
			case 3:
				objects[objects.size() - 1 - index]->setTexture(&explosionImg,
					sf::Vector2i(38, 41), sf::Vector2i(0, 168), 12, false);
				break;
			}
			break;
		case Object::AIR:
			switch (objects[objects.size() - 1 - index]->getSpriteNum())
			{
			case 0: //Weird thing 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 240), 1, false);
				break;
			case 1: //Weird thing 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 280), 1, false);
				break;
			case 2: //Regular Copter 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 320), 1, false);
				break;
			case 3: //Regular Copter 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 360), 1, false);
				break;
			case 4: //Fighter Jet 1a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 400), 1, false);
				break;
			case 5: //Fighter Jet 1b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 440), 1, false);
				break;
			case 6: //Fighter Jet Purple
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 480), 1, false);
				break;
			case 7: //Fighter Jet 2a
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 520), 1, false);
				break;
			case 8: //Fighter Jet 2b
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(32 * orient, 560), 1, false);
				break;
			case 9: //Big Copter Blades
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(64, 64), sf::Vector2i(520, 0), 3, false);
				break;
			case 10: //Advanced Mega Copter 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 96), sf::Vector2i(520, 64), 1, false);
				break;
			case 11: //Advanced Mega Copter 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 96), sf::Vector2i(560, 64), 1, false);
				break;
			case 12: //Big Plane 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(80, 88), sf::Vector2i(600, 64), 1, false);
				break;
			case 13: //Big Copter 
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(48, 72), sf::Vector2i(688, 64), 1, false);
				break;
			case 14: //Big Plane 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(80, 80), sf::Vector2i(600, 160), 1, false);
				break;
			case 15: //Side Bomber 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 320), 1, false);
				break;
			case 16: //Side Bomber 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 360), 1, false);
				break;
			case 17: //Dive Bomber 1
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 400), 1, false);
				break;
			case 18: //Dive Bomber 2
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(520 + 32 * orient, 440), 1, false);
				break;
			case 19: //Regular Copter Blades
				objects[objects.size() - 1 - index]->setTexture(&enemyImg,
					sf::Vector2i(32, 32), sf::Vector2i(688, 480), 3, false);
				break;
			default:
				objects[objects.size() - 1 - index]->setRandColor();
				break;
			}
			break;
		case Object::PLAYER_PROJECTILE: case Object::ENEMY_PROJECTILE:
			switch (objects[objects.size() - 1 - index]->getSpriteNum())
			{
			case 0:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(11, 18), sf::Vector2i((int)(rand() % 3) * 11, 0), 1, false);
				break;
			case 1:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(16, 30), sf::Vector2i((int)(rand() % 3) * 16, 19), 1, false);
				break;
			case 2:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(31, 30), sf::Vector2i((int)(rand() % 3) * 21, 50), 1, false);
				break;
			case 3:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(47, 46), sf::Vector2i((int)(rand() % 3) * 47, 81), 1, false);
				break;
			case 4:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(9, 28), sf::Vector2i((int)(rand() % 3) * 9, 128), 1, false);
				break;
			case 5:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(16, 32), sf::Vector2i((int)(rand() % 3) * 16, 157), 1, false);
				break;
			case 6:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(41, 44), sf::Vector2i((int)(rand() % 3) * 41, 190), 1, false);
				break;
			case 7:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(64, 48), sf::Vector2i((int)(rand() % 3) * 64, 235), 1, false);
				break;
			case 8:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(15, 29), sf::Vector2i((int)(rand() % 3) * 15, 284), 1, false);
				break;
			case 9: //Kunai
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(9, 31), sf::Vector2i(0, 314), 1, false);
				break;
			case 10:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(9, 31), sf::Vector2i((int)(rand() % 3) * 9, 346), 1, false);
				break;
			case 11:
				objects[objects.size() - 1 - index]->setTexture(&projectileImg,
					sf::Vector2i(16, 31), sf::Vector2i((int)(rand() % 3) * 16, 378), 1, false);
				break;
			case 12: //Enemy Projectile 1
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(8, 8), sf::Vector2i(0, 0), 4, false);
				break;
			case 13: //Breakable
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(14, 14), sf::Vector2i(0, 0), 4, false);
				break;
			case 14: //Breaking
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(16, 12), sf::Vector2i(0, 0), 5, true);
				break;
			case 15: //Big
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(12, 12), sf::Vector2i(0, 0), 2, false);
				break;
			case 16: //Medium
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(10, 10), sf::Vector2i(0, 0), 2, false);
				break;
			case 17: //One pixel projectile
				objects[objects.size() - 1 - index]->setTexture(&enemyProjectileImg,
					sf::Vector2i(4, 4), sf::Vector2i(0, 0), 1, false);
				break;
			case 18: //Missiles 
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
				objects[objects.size() - 1 - index]->setTexture(&missileImg,
					sf::Vector2i(12, 12), sf::Vector2i((orient % 5) * 12, 0), 1, false);
				break;
			}
			break;
		case Object::COLLECTABLE:
			switch (objects[objects.size() - 1 - index]->getID())
			{
			case 0:
				switch (country)
				{
				case 0:
					moneyOffset = 22;
					break;
				case 1:
					moneyOffset = 0;
					break;
				case 2:
					moneyOffset = 66;
					break;
				case 3:
					moneyOffset = 44;
					break;
				}
				objects[objects.size() - 1 - index]->setTexture(&moneyImg,
					sf::Vector2i(11, 12), sf::Vector2i(moneyOffset, 0), 2, false);
				break;
			case 1:
				objects[objects.size() - 1 - index]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 20), 8, false);
				break;
			case 2:
				objects[objects.size() - 1 - index]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 0), 8, false);
				break;
			case 3:
				objects[objects.size() - 1 - index]->setTexture(&powerUpImg,
					sf::Vector2i(16, 19), sf::Vector2i(0, 40), 8, false);
				break;
			}
		}
}

void Level::update(sf::Vector2u winSize)
{
	std::string s = "P1 Lives: " + std::to_string(p[0]->getHealth()) + "\nP2 Lives: " 
	+ std::to_string(p[1]->getHealth()) + "\nP1 Bombs: " + std::to_string(p[0]->getSpecialCharge()) 
	+ "\nP2 Bombs: " + std::to_string(p[1]->getSpecialCharge()) + "\nScore: 0";
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
	// so deleting doesn't shift everything down and mess up the for loop index
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

	//Random events!!!

	//Fly straight in formation
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, winSize.y * -0.25f);
	//	sf::Vector2f vel = sf::Vector2f(0, 4);

	//	for (int i = 0; i < 6; i++)
	//	{
	//		switch (i)
	//		{
	//		case 0:
	//			break;
	//		case 1:
	//			pos += sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y);
	//			break;
	//		case 2:
	//		case 4:
	//		case 5:
	//			pos += sf::Vector2f(0.1f * winSize.y, 0);
	//			break;
	//		case 3:
	//			pos += sf::Vector2f(-0.15f * winSize.y, -0.1f * winSize.y);
	//		}

	//		objects.push_back(new Air(0, true, winSize, &objects, pos, vel));
	//	}
	//}
	////Turn left
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, 
	//		winSize.y * -0.25f);
	//	sf::Vector2f vel = sf::Vector2f(0, 4);
	//	objects.push_back(new Air(1, true, winSize, &objects, pos, vel));
	//}
	////Turn Right
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x,
	//		winSize.y * -0.25f);
	//	sf::Vector2f vel = sf::Vector2f(0, 4);
	//	objects.push_back(new Air(1, true, winSize, &objects, pos, vel));
	//}
	////Flipping planes
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x,
	//		winSize.y * -0.25f);
	//	sf::Vector2f vel = sf::Vector2f(1, 7);

	//	objects.push_back(new Air(2, true, winSize, &objects, pos, vel));

	//	for (int i = 0; i < 3; i++)
	//	{
	//		pos += sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y);
	//		objects.push_back(new Air(2, true, winSize, &objects, pos, vel));
	//	}
	//}
	////Mini choppers left
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f(0, 0.15 * winSize.y);
	//	sf::Vector2f vel = sf::Vector2f(4, 0);
	//	objects.push_back(new Air(3, true, winSize, &objects, pos, vel));
	//}
	////Mini choppers right
	//if (rand() % 200 == -1)
	//{
	//	sf::Vector2f pos = sf::Vector2f(winSize.x, 0.15 * winSize.y);
	//	sf::Vector2f vel = sf::Vector2f(-4, 0);
	//	objects.push_back(new Air(3, false, winSize, &objects, pos, vel));
	//}

	switch (country)
	{
	case STATES:
		statesUpdate(winSize);
		break;
	case JAPAN:
		japanUpdate(winSize);
		break;
	case SWEDEN:
		swedenUpdate(winSize);
		break;
	case ENGLAND:
		englandUpdate(winSize);
	}
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
	//printf("inPos: %d, enabled: %d, dist: %f\n", int(infScrollInPos), int(infScrollEnabled), frontbackgroundDist);

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
	if (backgroundDist == 0)
	{
		if (!infScrollEnabled)
			setInfScroll(true);
		if (backgroundSpeedup < backgroundSpeedupMax)
			backgroundSpeedup += 0.01f;
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
	
	for (int i = objects.size() - 1; i >= 0; i--)
		if(objects.at(i)->getType() == -1)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 5)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 4)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 1 || objects.at(i)->getType() == 2)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 3)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 7)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 6)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 0)
			target.draw(*objects[i]);

	for (int i = objects.size() - 1; i >= 0; i--)
		if (objects.at(i)->getType() == 8)
			target.draw(*objects[i]);

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
			p[i]->shoot(objects);

		if (special)
			p[i]->special(objects, winSize);

		if (spawn) //Temporary and should be changed to continue.
		{
			p[0]->setHealth(3);
			p[1]->setHealth(3);
		}
	}
}
