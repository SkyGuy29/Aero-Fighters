#include "Cutscene.h"

Cutscene::Cutscene()
{
	
}

Cutscene::~Cutscene()
{

}

void Cutscene::load(int country, int level, bool player1, bool player2, sf::RenderWindow&)
{
	//identify which country,players, and level
	switch(country)
	{
	case England:
		if (player1 && !player2)
		{
			switch (level)
			{
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case Israel:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case Japan:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case Meddit:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Russia:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case Russia:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case States:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case States:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case Sweden:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case Sweden:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case Sweden:
				break;
			}
		}
		break;
	case Sweden:
		if (player1 && !player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			}
		}
		if (!player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			}
		}
		if (player1 && player2)
		{
			switch (level)
			{
			case England:
				break;
			case Israel:
				break;
			case Japan:
				break;
			case Meddit:
				break;
			case Russia:
				break;
			case States:
				break;
			}
		}
		break;
	}
}