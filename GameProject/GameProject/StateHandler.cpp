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

void StateHandler::initalize()
{
	currentState = new SplashScreen();
}

void StateHandler::loadContent()
{
	currentState -> loadContent();
}

void StateHandler::update()
{
	currentState -> update();
}

void StateHandler::draw(sf::RenderWindow &window)
{
	currentState -> draw(&window);
}