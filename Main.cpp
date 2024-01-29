#include <SFML/Graphics.hpp>

int main()
{
	sf::Clock clock;
	int deltaTime = 0, ups = 30;

	int scale = 3;
	sf::RenderWindow window(sf::VideoMode(320 * scale, 224 * scale), "Aero Fighters");
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
			if (!e.type)
				window.close();

		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / ups)
		{
			deltaTime -= 1000 / ups;
			
			// update game here
		}

		window.clear();

		// render game here

		window.display();
	}
	return 0;
}