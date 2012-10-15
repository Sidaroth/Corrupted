#pragma once

#include <string>
#include <iostream>

#include "GameState.h"
#include "SplashScreen.h"
#include "TitleScreen.h"

// Singleton class managing the state of the game (intro, menu, game, etc...)
class StateHandler
{
private:
	StateHandler();
	StateHandler(StateHandler const&); /// Copy constructor
	void operator=(StateHandler const&); /// Assignment operator

	GameState *currentState, *newState;

public:
	~StateHandler();
	static StateHandler &getInstance();

	void initalize();
	void loadContent();
	void unloadContent();
	void update();
	void draw(sf::RenderWindow &window);

	void addScreen(GameState *state);
};