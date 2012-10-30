#include "EnemyHandler.h"
#include "Vector2f.h"

void EnemyHandler::loadContent()
{
	for(short i = 0; i < 3; i++)
	{
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));
		
		if(m_EnemyVector[i] != NULL)
		{
			m_EnemyVector[i] -> loadContent();
		}
		else
		{
			std::cout << "Something Broke in enemy creation..." << std::endl;
			return;
		}
	}

	// Temporarily done so that the enemies don't spawn on top of eachother, so we can see them all
	for(short i = 0; i < 3; i++)
	{
		m_EnemyVector[i] -> setPosition(Vector2f(float(150 * (i + 5)), float(100 * (i + 5))));
	}
}

void EnemyHandler::unloadContent()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		delete m_EnemyVector[i];
	}
}

void EnemyHandler::draw()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw();
	}
}

void EnemyHandler::update()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> update();
	}
}

void EnemyHandler::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	this -> collisionMap = collisionMap;
	m_HorizontalSize = horizontalSize;

	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> setCollisionMap(collisionMap, horizontalSize);
	}
}