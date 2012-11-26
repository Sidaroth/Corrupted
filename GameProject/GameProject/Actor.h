#pragma once		// make sure it's only included once. 

#include "Vector2f.h"	
#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>


class Actor
{
protected:
	sf::Texture m_Texture;

	struct actionTexture
	{
		sf::Texture imgTexture;
		int size;
	};

	std::map<std::string,actionTexture> m_TexturesActions;


	Vector2f m_Position;		// Hmm.. Sprite has a position, so is this needed? we'll see...
	sf::Sprite m_Sprite;
	short m_shSpriteSize;		//The width/height of a frame in the spritesheet

	void setSprite();

	virtual bool loadContent();

public:
	
	enum TextureType
	{
		MOVE,
		ATTACK,
		STILL,
		DIE
	};

	// Do we need all these constructors?
	Vector2f* getSpritePosition();
	void setPosition(Vector2f newPos);
	void draw();
	sf::Sprite getSprite();
	Actor();
	Actor(int x, int y);
	Actor(int x, int y, sf::Sprite sprite);
	Actor(sf::Sprite sprite);
	void setSpriteSize(short size);

	Vector2f* getPosition();
	float getXPosition();
	float getYPosition();
};