#include "Level1.h"

Level1::Level1()
{
	// NATH'N!
}

void Level1::loadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	text.setPosition(100, 50);
	text.setString("Level 1");
	text.setFont(font);
}

void Level1::unloadContent()
{

}

void Level1::update()
{

}

void Level1::draw(sf::RenderWindow &window)
{
	window.draw(text);
}