#include "Level1.h"


Level1::Level1()
{
	
}

void Level1::loadContent()
{
	superLoadContent();
	text.setPosition(100, 50);
	text.setString("Level 1");
	text.setFont(font);
}
/*
void Level1::unloadContent()
{

}

void Level1::processEvents(sf::Event event)
{
		
}

void Level1::update()
{
	
}
*/
void Level1::draw(sf::RenderWindow &window)
{
		superDraw(window);
		window.draw(text);
}