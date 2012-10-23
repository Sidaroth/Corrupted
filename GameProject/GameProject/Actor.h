#include "Vector2f.h"	
#include <iostream>
#include "SFML/Graphics.hpp"

#pragma once		// make sure it's only included once. 

class Actor
{
protected:
	sf::Texture m_Texture;
	Vector2f m_Position;		// Hmm.. Sprite has a position, so is this needed? we'll see...
	sf::Sprite m_Sprite;
	short m_shSpriteSize;		//The width/height of a frame in the spritesheet

	
	Vector2f* getPosition();
	void setSprite();

	virtual bool loadContent();

public:
	// Do we need all these constructors?
	void setPosition(int x, int y);
	void draw();
	sf::Sprite getSprite();
	Actor();
	Actor(int x, int y);
	Actor(int x, int y, sf::Sprite sprite);
	Actor(sf::Sprite sprite);
	void setSpriteSize(short size);
};