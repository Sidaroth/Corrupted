#include "EnemyHandler.h"

void EnemyHandler::loadContent()
{
	for(int i = 0; i < 3; i++)
	{
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));
		m_EnemyVector[i] -> loadContent();
	}

	for(int i = 0; i < 3; i++)
	{
		m_EnemyVector[i] -> setPosition(100 * (i + 5), 100 * (i + 5));
	}
}

void EnemyHandler::unloadContent()
{

}

void EnemyHandler::draw(sf::RenderWindow &window)
{
	for(int i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw(window);
	}
}

void EnemyHandler::update()
{

}