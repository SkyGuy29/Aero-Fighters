#include "VideoCutscene.h"


bool VideoCutscene::draw(sf::RenderWindow& window)
{
		loadImage(id);
		window.draw(frame);
		return index < lastFrame;
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
				  return cutsceneID::STATES;
		    }
  	  case Countries::JAPAN:
			  switch (player)
			  {
			  case 1:
				  return cutsceneID::HEIN;
			  case 2:
				  return cutsceneID::MAO;
			  case 3:
				  return cutsceneID::JAPAN;
			  }
      case Countries::SWEDEN:
				switch (player)
				{
				  case 1:
					  return cutsceneID::KOHFUL;
				  case 2:
					  return cutsceneID::TEEBEE;
				  case 3:
					  return cutsceneID::SWEDEN;
				}
			case Countries::ENGLAND:
				switch (player)
				{
				case 1:
					return cutsceneID::VILLIAM;
				case 2:
					return cutsceneID::WHITE;
				case 3:
					return cutsceneID::ENGLAND;
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
			while (!image.loadFromFile("intro" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::OSARU:
			while (!image.loadFromFile("osaru" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::PANDORA:
			while (!image.loadFromFile("pandora" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KEATON:
			while (!image.loadFromFile("keaton" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KEATH:
			while (!image.loadFromFile("keath" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::STATES:
			while (!image.loadFromFile("states" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::HEIN:
			while (!image.loadFromFile("hein" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::MAO:
			while (!image.loadFromFile("mao" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::JAPAN:
			while (!image.loadFromFile("japan" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::KOHFUL:
			while (!image.loadFromFile("kohful" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::TEEBEE:
			while (!image.loadFromFile("teebee" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::SWEDEN:
			while (!image.loadFromFile("sweden" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::VILLIAM:
			while (!image.loadFromFile("villiam" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::WHITE:
			while (!image.loadFromFile("white" + std::to_string(index++) + ".png")) {}
			break;
		case cutsceneID::ENGLAND:
			while (!image.loadFromFile("england" + std::to_string(index++) + ".png")) {}
		}
		frame.setTexture(image);
}
