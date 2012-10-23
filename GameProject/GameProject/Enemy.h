#pragma once

#include "SFML/Graphics.hpp"
#include "Character.h"

/// The generic "interface" for our enemies. All types of enemies will inherit from this class
class Enemy : public Character
{
protected:
	short m_shSoulsToDrop;

public:
	virtual void sayHello() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual bool loadContent() = 0;
};