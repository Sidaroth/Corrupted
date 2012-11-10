#include "EnemyHandler.h"
#include "Vector2f.h"

void EnemyHandler::loadContent(EnvironmentHandler* level)
{
	m_Level = level;
	m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));
		
	if(m_EnemyVector[0] != NULL)
	{
		std::cout << "Enemy created!\n";
		m_EnemyVector[0] -> loadContent();
	}
	else
	{
		std::cout << "Something Broke in enemy creation..." << std::endl;
		return;
	}

	m_EnemyVector[0] -> setEnvironmentLevel(m_Level);
	m_EnemyVector[0] -> setPosition(Vector2f(960, 960));
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