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
	// delete all pointers. 
	delete currentState;
	delete newState;
	delete m_pWindow;
}

void StateHandler::addScreen(GameState *state)
{
	currentState -> unloadContent();
	delete currentState;
	
	currentState = state;
	currentState -> loadContent(m_pWindow);
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
	currentState -> loadContent(window);
}

void StateHandler::processEvents(sf::Event event)
{
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