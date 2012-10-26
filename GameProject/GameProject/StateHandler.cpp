#include "StateHandler.h"

StateHandler &StateHandler::getInstance()
{
	static StateHandler instance;
	return instance;
}

StateHandler::StateHandler()
{

}

StateHandler::~StateHandler()
{

}

void StateHandler::addScreen(GameState *state)
{
	currentState -> unloadContent();
	delete currentState;
	
	currentState = state;
	currentState -> loadContent();
}

void StateHandler::initalize()
{
	currentState = NULL;
}

void StateHandler::setStartState(GameState* state)
{
	currentState = state;
}

void StateHandler::loadContent()
{
	currentState -> loadContent();
}

void StateHandler::processEvents(sf::Event event)
{
	currentState -> processEvents(event);
}

void StateHandler::update()
{
	currentState -> update();
}

void StateHandler::draw(sf::RenderWindow &window)
{
	currentState -> draw(window);
}