#include "SuperLevel.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "SplashScreen.h"

SuperLevel::SuperLevel()
{
	m_Level = new EnvironmentHandler();
	m_EnemyHandler = new EnemyHandler();
}

SuperLevel::~SuperLevel()
{

}

void SuperLevel::superLoadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	player = new Player();
	player -> loadContent();	
	player -> setEnvironmentLevel(m_Level);

	ui = new Ui();
	ui->loadContent();

	m_Level -> loadContent();

	m_EnemyHandler -> loadContent();
	m_EnemyHandler -> setCollisionMap(m_Level -> getObjectVector(), m_Level -> getHorizontalBitmapSize());

	player -> setPosition(m_Level -> getPlayerPosition());
	keyControl = new KeyboardController(player);
	
	m_Viewport.reset(sf::FloatRect(0, 0, 1366, 768));
	m_Viewport.setViewport(sf::FloatRect(0.0f, 0.0f,1.f, 1.0f));
	m_Viewport.setCenter(1366/2, 768/2);
	m_Viewport.zoom(1.5);
}

void SuperLevel::unloadContent()
{

}

void SuperLevel::processEvents(sf::Event event)
{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			StateHandler::getInstance().addScreen(new TitleScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			StateHandler::getInstance().addScreen(new SplashScreen);
		}
}

void SuperLevel::update()
{
	player -> animation();
	player -> update();
	ui -> update();
	keyControl->checkPressed();
	m_EnemyHandler -> update();

	m_Viewport.setCenter(player -> getXPosition(), player -> getYPosition());
}

void SuperLevel::superDraw(sf::RenderWindow &window)
{	
	m_Level -> draw(window);
	m_EnemyHandler -> draw(window);
	player -> draw(window);
	ui->draw(window);
	window.setView(m_Viewport);
}