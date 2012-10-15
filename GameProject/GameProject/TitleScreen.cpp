#include "TitleScreen.h"

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

void TitleScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}