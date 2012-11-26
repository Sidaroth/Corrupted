#include "Game.h"

int main()
{
	// Starts a new game, the game class holds the main game loop etc.
	Game* game;
	game = new Game();	
	game -> start();
	
	//delete game;
	return EXIT_SUCCESS;
}