#pragma once

#include <string>
#include <iostream>

#include "GameState.h"

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
	sf::RenderWindow* m_pWindow;
	void initalize();
	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();
	
	void setStartState(GameState* state);
	void addScreen(GameState *state);
};