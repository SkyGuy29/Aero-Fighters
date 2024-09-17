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

	/*
	Ben, Matthew, Gabe, I want to say a huge thank you for the past three
	months of work you have put in. I think you guys have probably seen that
	I was not super hopeful about this project by any means, but truly despite
	the challenges I knew we would face you all three took it on head first.
	None of us were perfect, and I think this project stands as a testament to
	that, but it also shows just how far hard work can get you. You gave it your
	all to a project I thought was doomed from the start, and showed me so much
	hope and passion where I fell short.

	Matthew, man you are so committed. You have been probably the hardest worker
	I have ever met. Every day, besides the Inspirobot incident, you came in and
	got started immediatly. I really appreciate all the effort you put in here,
	seriously you have made such a massive impact on me with just how hard you
	worked (and all without complaining!). You really are unstoppable.

	Gabe, seeing you both shine on stage and on this project has been really
	awe-inspiring. You are really talented, and I'm so glad I was able to work
	with you on this project. I'm sure I can speak for all of us when I say that
	our group was made so much better with you here. Thank you so much for what
	you contributed here, I hope that whatever path you take in your life, CS or
	not, will take you to success.

	Ben, I think I've already told you this, but the one thing I wanted more than
	anything else was to work with you on this project. You are a great friend,
	and an even better programmer. I hope you learned a lot from working on this,
	because for a long time I was pretty convinced that you already knew everything.
	I know I learned so much from you already, and we still have another year to go.
	I'm really excited to see where both of our futures lead us. Tanks so much for 
	the wonderful memories we made together during these months.
	
	Mr. Graham, if you are reading this, thank you for all of the advice you gave me
	throughout this project. I still do not quite feel confident as a leader, but you
	saw the best in me and gave me encouragement when I needed it most. I probably
	should have paid more attention to the nudges you gave me along the way, but
	I think somehow we made it almost work in the end.

	In closing, I just want to say one last thank you to all of you. It means the
	world to me that you guys wanted me to lead this project, and I hope I was at
	least somewhat able to live up to the claims I made in the beginning.

	Sincerely,
		-Christian.
	*/
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
   /\/\|  |  |  |  |  |  |/\/\
  ('w' |  |     |  |  |  | 'w')
   \_____/ \___/ \___/ \_____/

		   Inch Cats


		___   ___   ___
	   /   \ /   \ /   \
      |  |  |  |  |  |  |/\/\
    __|  |  |  |     |  | 'w')
   (____/ \___/ \___/ \_____/

		   Stac Hcni

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
		 ___   ___   ___
		/   \ /   \ /   \
   /\/\|  |  |  |  |  |  |
  ('o' |  |     |  |  |  |__
   \_____/ \___/ \___/ \____)

		   CInch at
*/