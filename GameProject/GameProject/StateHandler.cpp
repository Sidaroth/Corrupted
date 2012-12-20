#include "StateHandler.h"
#include <assert.h>

StateHandler &StateHandler::getInstance()
{
	static StateHandler instance;
	instance.safe = true;
	return instance;
}

StateHandler::StateHandler()
{

}

StateHandler::~StateHandler()
{
	// delete all pointers. 
	// delete currentState;
	// delete newState;
	// delete m_pWindow;
}

void StateHandler::addScreen(GameState *state)
{
	safe = false;
	currentState -> unloadContent();
	//delete currentState;
	
	currentState = state;
	currentState -> loadContent();
	safe = true;
}

void StateHandler::initalize()
{
	currentState = NULL;
}

void StateHandler::setStartState(GameState* state)
{
	currentState = state;
}

void StateHandler::loadContent(sf::RenderWindow* window)
{	
	m_pWindow = window;
	currentState -> loadContent();
}

void StateHandler::processEvents(sf::Event event)
{
	assert(safe);
	currentState -> processEvents(event);
}

void StateHandler::update()
{
	currentState -> update();
}

void StateHandler::draw()
{
	currentState -> draw();
}