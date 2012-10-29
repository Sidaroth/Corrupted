#include "Level1.h"


Level1::Level1()
{
	m_Level = new EnvironmentHandler();
	m_EnemyHandler = new EnemyHandler();
}

void Level1::loadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	player = new Player();
	player -> loadContent();	
	player -> setEnvironmentLevel(m_Level);

	text.setPosition(100, 50);
	text.setString("Level 1");
	text.setFont(font);

	m_Viewport.reset(sf::FloatRect(0, 0, 1366, 768));
	m_Viewport.setViewport(sf::FloatRect(0.0f, 0.0f,1.f, 1.0f));
	m_Viewport.setCenter(1366/2, 768/2);
	m_Viewport.zoom(1.5);
	m_Level -> loadContent();
	m_EnemyHandler -> loadContent();
	player -> setPosition(m_Level -> getPlayerPosition());
	keyControl = new KeyboardController(player);
}

void Level1::unloadContent()
{

}

void Level1::update()
{
	player -> animation();
	player -> update();
	keyControl->checkPressed();

	m_Viewport.setCenter(player -> getXPosition(), player -> getYPosition());
}

void Level1::draw(sf::RenderWindow &window)
{
	window.setView(m_Viewport);
	m_Level -> draw(window);
	m_EnemyHandler -> draw(window);
	window.draw(text);
	player -> draw(window);
}