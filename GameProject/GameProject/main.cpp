#include "Game.h"

int main()
{
	// Starts a new game, the game class holds the main game loop etc.
	Game* game;
	game = Game::getInstance();
	game -> start();
	
	return EXIT_SUCCESS;
}