#include "Level1.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Level1::Level1()
{
	m_Level = new EnvironmentHandler();
	m_EnemyHandler = new EnemyHandler();
	std::cout << "Level created!\n";
}

Level1::~Level1()
{
	delete m_Level;
	delete m_EnemyHandler;
}

void Level1::loadContent()
{
	superLoadContent();

	m_EnemyHandler -> loadContent(m_Level);
	m_EnemyHandler -> setCollisionMap(m_Level -> getObjectVector(), m_Level -> getHorizontalBitmapSize());
	
}

void Level1::draw()
{
	superDraw();
}