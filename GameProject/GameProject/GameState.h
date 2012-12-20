#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// Abstract state class.. 
class GameState
{
public:
	virtual void loadContent() = 0;
	virtual void unloadContent() = 0;
	virtual void processEvents(sf::Event event) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	sf::RenderWindow* m_pWindow;
};