#pragma once

#include <SFML/Graphics.hpp>

// Abstract state class.. 
class GameState
{
public:
	GameState();
	~GameState();

	virtual void loadContent();
	virtual void unloadContent();
	virtual void update();
	virtual void draw(sf::RenderWindow &window);
};