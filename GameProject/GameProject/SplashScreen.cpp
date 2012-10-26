#include "SplashScreen.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "Level1.h"

SplashScreen::SplashScreen()
{
	// NATH'N!
}

void SplashScreen::loadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	text.setPosition(100, 50);
	text.setString("SplashScreen");
	std::cout << "DAFAQ" << std::endl;
	text.setFont(font);
}

void SplashScreen::unloadContent()
{

}

void SplashScreen::update()
{

}

void SplashScreen::processEvents(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		StateHandler::getInstance().addScreen(new Level1);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		StateHandler::getInstance().addScreen(new TitleScreen);
	}
}

void SplashScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}