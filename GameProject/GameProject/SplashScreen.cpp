#include "SplashScreen.h"

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
	text.setFont(font);
}

void SplashScreen::unloadContent()
{

}

void SplashScreen::update()
{

}

void SplashScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}