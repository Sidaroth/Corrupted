#include "Vector2f.h"	
#include "SFML/Graphics.hpp"

#pragma once		// make sure it's only included once. 

class Actor
{
private:
	Vector2f m_Position;		// Hmm.. Sprite has a position, so is this needed? we'll see...
	sf::Sprite m_Sprite;

public:
	// Do we need constructors?
	Actor();
	Actor(int x, int y);
	Actor(int x, int y, sf::Sprite sprite);
	Actor(sf::Sprite sprite);
};