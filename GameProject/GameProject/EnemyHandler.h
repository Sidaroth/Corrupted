#pragma once

#include "EnemyFactory.h"
#include "SFML/Graphics.hpp"

class EnemyHandler
{
protected:
	EnemyFactory* m_EnemyFactory;
	std::vector<Enemy*> m_EnemyVector;

public:
	void loadContent();
	void unloadContent();
	void setCollisionMap(std::vector<bool>* collisionMap);
	void draw(sf::RenderWindow &window);
	void update();
};