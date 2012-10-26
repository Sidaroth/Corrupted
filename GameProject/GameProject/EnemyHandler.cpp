#include "EnemyHandler.h"
#include "Vector2f.h"

void EnemyHandler::loadContent()
{
	for(short i = 0; i < 3; i++)
	{
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));
		m_EnemyVector[i] -> loadContent();
	}

	// Temporarily done so that the enemies don't spawn on top of eachother, so we can see them all
	for(short i = 0; i < 3; i++)
	{
		m_EnemyVector[i] -> setPosition(Vector2f(100 * (i + 5), 100 * (i + 5)));
	}
}

void EnemyHandler::unloadContent()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		delete m_EnemyVector[i];
	}
}

void EnemyHandler::draw(sf::RenderWindow &window)
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw(window);
	}
}

void EnemyHandler::update()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> update();
	}
}