#pragma once

#include "EnemyFactory.h"
#include "SFML/Graphics.hpp"
#include "Environment.h"

class EnemyHandler
{
protected:
	EnemyFactory* m_EnemyFactory;
	EnvironmentHandler* m_Level;
	short m_HorizontalSize;				// --- 
	std::vector<bool>* collisionMap;	// Are these 2 really needed? 
	std::vector<Enemy*> m_EnemyVector;

public:
	~EnemyHandler();
	void loadContent(EnvironmentHandler* level);
	void unloadContent();
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	void draw();
	void update(Vector2f* playerPos);
	std::vector<Enemy*>* getEnemyVector( );
};