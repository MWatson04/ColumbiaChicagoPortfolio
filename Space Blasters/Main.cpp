#include <ctime>

#include "Game.h"


int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	// Game class instance
	Game game;

	// Run game
	game.Run();

	// End of application
	return 0;
}
