#pragma once		// make sure it's only included once. 

#include "Vector2f.h"	
#include "SFML/Graphics.hpp"
#include "Game.h"


class Actor
{
private:
	sf::Texture m_Texture;
	Vector2f m_Position;		// Hmm.. Sprite has a position, so is this needed? we'll see...
	sf::Sprite m_Sprite;

protected:
	void setPosition(int x, int y);
	Vector2f* getPosition();
	void setSprite();
	Game game;
	

public:
	// Do we need all these constructors?
	bool loadContent();
	void draw();
	Actor();
	Actor(int x, int y);
	Actor(int x, int y, sf::Sprite sprite);
	Actor(sf::Sprite sprite);
};