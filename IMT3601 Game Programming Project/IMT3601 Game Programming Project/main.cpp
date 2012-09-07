#include <iostream>
#include "..\SDL-1.2.15\include\SDL.h"   //should be fixed
#include <cstdio>

using namespace std;

int main(int argc, char* args[])
{
	// Hello world test. 
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL; 

	// Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Set up screen
	screen = SDL_SetVideoMode( 320, 240, 32, SDL_SWSURFACE );

	// Load Image
	hello = SDL_LoadBMP("../Resources/helloworld.bmp");

	// Apply image to screen
	SDL_BlitSurface( hello, NULL, screen, NULL );

	// Update screen
	SDL_Flip( screen );

	// Pause
	SDL_Delay( 7000 );
	
	// Free the loaded image
	SDL_FreeSurface( hello );

	// Quit SDL
	SDL_Quit();

	return 0;
}