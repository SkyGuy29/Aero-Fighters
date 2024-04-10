// the fun begins!

/*
	Start here, then Game takes over.

	Game runs the main loop at 30 updates and frames a second (until the original is found).
	Game also handles the window scaling and events.
	Game updates and draws level every loop.

	winSize is the resolution of the original game. It is NOT the size of the window.
	All window scaling is handled elsewhere. No scaling math needed.

	Level loads the enemy placement from a file and controls the characters.
	Level handles player input (keyboard and controller). Maybe could be moved back to Game.
	Level updates the background, projectiles, enemies, players, and collectables.

	Player can shoot by passing a pointer of the playerProjs vector, and pushing a projectile to it.
	Player is moved by level's getInput method. (WASD, IJKL) OR (Left Stick)

	Projectiles are created at the position of an enemy or player and stored in a vector in Level.
	Projectiles just fly in a straight line at their angle. Other types will be added later.
*/

#include "Game/Game.h"

int main()
{
	Game game;
	game.run();
	return 0;
}

/*
         ___   ___   ___
        /   \ /   \ /   \
   /\/\|  |  |  |  |  |  |
  ('w' |  |     |  |  |  |__
   \_____/ \___/ \___/ \____)

           Inch Cat

         ___   ___   ___
        /   \ /   \ /   \
   /\/\|  |  |  |  |  |  |
  ('w' |  |     |  |  |  |__
   \_____/ \___/ \___/ \____)

           Inch Cat

         ___   ___   ___
        /   \ /   \ /   \
   /\/\|  |  |  |  |  |  |
  ('w' |  |     |  |  |  |__
   \_____/ \___/ \___/ \____)

           Inch Cat
*/