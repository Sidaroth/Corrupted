#include <iostream>
#include <SDL.h>
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
	hello = SDL_LoadBMP("helloworld.bmp");

	// Apply image to screen
	SDL_BlitSurface( hello, NULL, screen, NULL );

	// Update screen
	SDL_Flip( screen );

	// Pause
	SDL_Delay( 2000 );
	
	// Free the loaded image
	SDL_FreeSurface( hello );

	// Quit SDL
	SDL_Quit();

	return 0;
}