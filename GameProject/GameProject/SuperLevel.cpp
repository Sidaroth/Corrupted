#include "SuperLevel.h"
#include "StateHandler.h"
// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "SplashScreen.h"

SuperLevel::SuperLevel()
{

}

SuperLevel::~SuperLevel()
{

}

void SuperLevel::superLoadContent(sf::RenderWindow* window)
{
	m_pWindow = window;
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_Level -> loadContent();

	player = new Player();
	player -> loadContent();	
	player -> setEnvironmentLevel(m_Level);
	player -> setEnemyVector( m_EnemyHandler->getEnemyVector( ) );

	//ui = new Ui();
	//ui->loadContent();

	player -> setPosition(m_Level -> getPlayerPosition());
	
	//keyControl = new KeyboardController(player,StateHandler::getInstance().m_pWindow);
	
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
	//	keyControl->checkMouse(event);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			StateHandler::getInstance().addScreen(new TitleScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			StateHandler::getInstance().addScreen(new SplashScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			player -> takeDamage(5);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			player -> takeDamage(-5);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			 if(!player->isDoingAction())
			 {
				player->changeAnimationToStand();
			 }
		}
}

void SuperLevel::update()
{
	player -> animation();
	player -> update();
//	ui -> update(player);
//	keyControl->checkPressed();
	m_EnemyHandler -> update();

	m_Viewport.setCenter(player -> getXPosition(), player -> getYPosition());
}

void SuperLevel::superDraw()
{	
	m_Level -> draw();
	m_EnemyHandler -> draw();
	player -> draw();
	//ui->draw();
	StateHandler::getInstance().m_pWindow->setView(m_Viewport);
}