#pragma once

#include "SFML/Graphics.hpp"
#include "Character.h"
#include <list>
#include "Vector2f.h"
#include "Point.h"

#define TILESIZE 96

/// The generic class for our enemies. All types of enemies will inherit from this class
class Enemy : public Character
{
protected:
	short m_shSoulsToDrop;
	std::vector<bool>* collisionMap;
	short m_HorizontalBitmapSize;
	short m_VerticalBitmapSize;

public:
	virtual void sayHello() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	virtual bool loadContent() = 0;
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	std::vector<Vector2f*> findPath(int startX, int startY, int goalX, int goalY);
};