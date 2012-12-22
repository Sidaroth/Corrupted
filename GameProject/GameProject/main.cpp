#include "Game.h"
#include <Windows.h>

int main()
{

#if (NDEBUG)
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif

	// Starts a new game, the game class holds the main game loop etc.
	Game* game;
	game = new Game();	
	game -> start();
	
	//delete game;
	return EXIT_SUCCESS;
}