#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
	sf::Clock clock;
	int deltaTime = 0;
	
	// Change later maybe
	const int UPDATES_PER_SEC = 30, FRAMES_PER_SEC = 30;
	float scale = 2.f;

	sf::RenderWindow window(sf::VideoMode(224 * scale, 320 * scale), "Aero Fighters");
	window.setFramerateLimit(FRAMES_PER_SEC);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
			if (!e.type)
				window.close();

		deltaTime += clock.restart().asMilliseconds();
		while (deltaTime >= 1000 / UPDATES_PER_SEC)
		{
			deltaTime -= 1000 / UPDATES_PER_SEC;
			
			// update game here
		}

		window.clear();

		// render game here

		window.display();
	}
	return 0;
}