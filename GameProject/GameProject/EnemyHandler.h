#pragma once

#include "EnemyFactory.h"
#include "SFML/Graphics.hpp"

class EnemyHandler
{
protected:
	EnemyFactory* m_EnemyFactory;
	short m_HorizontalSize;				// --- 
	std::vector<bool>* collisionMap;	// Are these 2 really needed? 
	std::vector<Enemy*> m_EnemyVector;

public:
	void loadContent();
	void unloadContent();
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	void draw();
	void update();
};