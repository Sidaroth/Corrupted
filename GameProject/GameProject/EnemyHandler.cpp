#include "EnemyHandler.h"
#include "Vector2f.h"

EnemyHandler::EnemyHandler()
{
	m_EnemyFactory = new EnemyFactory();
}

EnemyHandler::~EnemyHandler()
{
	for( std::vector<Enemy*>::iterator it = m_EnemyVector.begin(); it != m_EnemyVector.end();)
	{
		delete * it;
		it = m_EnemyVector.erase(it);
	}
}

void EnemyHandler::loadContent(EnvironmentHandler* level)
{
	m_Level = level;
	m_EnemyFactory -> loadContent();
	m_EnemyVector.reserve(500);

	int x = 96;
	int y = 96;

	for(int i = 0; i < 100; i++)
	{	
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));

		if(m_EnemyVector[i] != NULL)
		{
			std::cout << "Enemy created!\n";
			m_EnemyVector[i] -> loadContent();
		}
		else
		{
			std::cout << "Something Broke in enemy creation..." << std::endl;
			return;
		}

		x += i * 96;

		if(x >= 5000)
		{
			y += 96;
			x = 96;
		}

		m_EnemyVector[i] -> setEnvironmentLevel(m_Level);
		m_EnemyVector[i] -> setPosition(Vector2f(x, y));
	}
}

void EnemyHandler::unloadContent()
{
	for( std::vector<Enemy*>::iterator it = m_EnemyVector.begin(); it != m_EnemyVector.end();)
	{
		delete * it;
		it = m_EnemyVector.erase(it);
	}
}

void EnemyHandler::draw()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw();
	}
}

void EnemyHandler::update(Vector2f* playerPos)
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> update(playerPos);
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

std::vector<Enemy*>* EnemyHandler::getEnemyVector( )
{
	return &m_EnemyVector;
}