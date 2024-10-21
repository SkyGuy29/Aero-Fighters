#include "VideoCutscene.h"
#include <iostream>


bool VideoCutscene::drawTo(sf::RenderWindow& window)
{
	loadImage();
	window.draw(frame);
	return index < id;
}


//things needed to determine the VideoCutscene:
//if the boss was killed before the time ran out		bool, is this in Game or Level?
//if it was, which country are we and which				4 options stored in Game
//players are playing.									3 options stored in Game (p1 p2 or both)
//if not, which final boss it was						2 options, is this in Game or Level?

cutsceneID VideoCutscene::getID(bool bossKilled, bool pandoraWasBoss, int player, Countries country)
{
	if (bossKilled)
		switch (country)
		{
		case Countries::STATES:
			switch (player)
			{
				case 1:
					return cutsceneID::KEATON;
				case 2:
					return cutsceneID::KEATH;
				case 3:
					return cutsceneID::P1P2STATES;
			}
  		case Countries::JAPAN:
			  switch (player)
			  {
			  case 1:
				  return cutsceneID::HEIN;
			  case 2:
				  return cutsceneID::MAO;
			  case 3:
				  return cutsceneID::P1P2JAPAN;
			  }
		case Countries::SWEDEN:
			switch (player)
			{
			  case 1:
				  return cutsceneID::KOHFUL;
			  case 2:
				  return cutsceneID::TEEBEE;
			  case 3:
				  return cutsceneID::P1P2SWEDEN;
			}
		case Countries::ENGLAND:
			switch (player)
			{
			case 1:
				return cutsceneID::VILLIAM;
			case 2:
				return cutsceneID::WHITE;
			case 3:
				return cutsceneID::P1P2ENGLAND;
			}
		}
		else
 			if (pandoraWasBoss)
				return cutsceneID::PANDORA;
			else
				return cutsceneID::OSARU;
}


void VideoCutscene::loadImage()
{
	//the while loop keeps increasing the index variable until it finds a successful load.
	switch (id)
	{
	case cutsceneID::START:
		if (index < 94)
			index = 94;
		image.loadFromFile("res/Cutscenes/intro/intro" + std::to_string(index++) + ".png");
		break;						   	
	case cutsceneID::OSARU:			   	
		while (!image.loadFromFile("res/Cutscenes/osaru/osaru" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::PANDORA:		   	
		while (!image.loadFromFile("res/Cutscenes/pandora/pandora" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::KEATON:		   	
		while (!image.loadFromFile("res/Cutscenes/keaton/keaton" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::KEATH:			   	
		while (!image.loadFromFile("res/Cutscenes/keath/keath" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::P1P2STATES:	   	
		while (!image.loadFromFile("res/Cutscenes/states/states" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::HEIN:			   	
		while (!image.loadFromFile("res/Cutscenes/hein/hein" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::MAO:			   	
		while (!image.loadFromFile("res/Cutscenes/mao/mao" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::P1P2JAPAN:		   	
		while (!image.loadFromFile("res/Cutscenes/japan/japan" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::KOHFUL:		   	
		while (!image.loadFromFile("res/Cutscenes/kohful/kohful" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::TEEBEE:		   	
		while (!image.loadFromFile("res/Cutscenes/teebee/teebee" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::P1P2SWEDEN:	   	
		while (!image.loadFromFile("res/Cutscenes/sweden/sweden" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::VILLIAM:		   	
		while (!image.loadFromFile("res/Cutscenes/villiam/villiam" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::WHITE:			   	
		while (!image.loadFromFile("res/Cutscenes/white/white" + std::to_string(index++) + ".png")) {}
		break;						   	
	case cutsceneID::P1P2ENGLAND:	   	
		while (!image.loadFromFile("res/Cutscenes/england" + std::to_string(index++) + ".png")) {}
	}
	frame.setTexture(image);
}
