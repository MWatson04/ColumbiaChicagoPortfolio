#include <ctime>

#include "Game.h"


int main()
{
	// Initialize random seed (srand)
	srand(static_cast<unsigned>(time(NULL)));

	// Make instance of game class
	Game game;

	// Run game
	game.Run();

	// End of application
	return 0;
}
