#include "TitleScreen.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "Level1.h"
#include "SplashScreen.h"

TitleScreen::TitleScreen()
{
	// NATH'N!
}

void TitleScreen::loadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	text.setPosition(100, 50);
	text.setString("TitleScreen");
	text.setFont(font);
}

void TitleScreen::unloadContent()
{

}

void TitleScreen::update()
{

}

void TitleScreen::processEvents(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		StateHandler::getInstance().addScreen(new Level1);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		StateHandler::getInstance().addScreen(new SplashScreen);
	}
}

void TitleScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}