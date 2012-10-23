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
	

	text.setPosition(100, 50);
	text.setString("Level 1");
	text.setFont(font);

	m_Viewport.reset(sf::FloatRect(0, 0, 1366, 768));
	m_Viewport.setViewport(sf::FloatRect(0.0f, 0.0f,1.f, 1.0f));
	m_Viewport.setCenter(1366/2, 768/2);
	m_Viewport.zoom(2);
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
	keyControl->checkPressed();
}

void Level1::draw(sf::RenderWindow &window)
{
	window.setView(m_Viewport);
	m_Level -> draw(window);
	player -> draw(window);
	m_EnemyHandler -> draw(window);
	window.draw(text);
}