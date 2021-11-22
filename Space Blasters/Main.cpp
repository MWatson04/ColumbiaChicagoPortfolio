#include "Game.h"
#include <ctime>

int main()
{
	// Initialize random seed (srand)
	srand(static_cast<unsigned>(time(0)));

	// Make instance of game class
	Game game;

	// Run game
	game.Run();

	// End of application
	return 0;
}
