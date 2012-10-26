#pragma once

#include "SFML/Graphics.hpp"
#include "Character.h"
#include <list>
#include "Vector2f.h"
#include "Point.h"

/// The generic class for our enemies. All types of enemies will inherit from this class
class Enemy : public Character
{
protected:
	short m_shSoulsToDrop;

public:
	virtual void sayHello() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	virtual bool loadContent() = 0;
	std::vector<Vector2f*> findPath(Vector2f* start, Vector2f* goal);
};