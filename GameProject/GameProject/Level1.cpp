#include "Level1.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "SplashScreen.h"
#include "StateHandler.h"

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

void Level1::loadContent(sf::RenderWindow* window)
{
	superLoadContent(window);

	m_EnemyHandler -> loadContent(m_Level);
	m_EnemyHandler -> setCollisionMap(m_Level -> getObjectVector(), m_Level -> getHorizontalBitmapSize());
	
	text.setPosition(100, 50);
	text.setString("Level 1");
	text.setFont(font);
}

void Level1::draw()
{
	superDraw();
	StateHandler::getInstance().m_pWindow->draw(text);
}

//void Level1::unloadContent()
//{
//}
//
//void Level1::processEvents(sf::Event event)
//{
//}
//
//void Level1::update()
//{
//}