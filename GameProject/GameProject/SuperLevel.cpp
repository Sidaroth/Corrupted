#include "SuperLevel.h"
#include "StateHandler.h"
// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "SplashScreen.h"
#include "Highscore.h"

SuperLevel::SuperLevel()
{

}

SuperLevel::~SuperLevel()
{
	// Delete all pointers.
	delete m_Level;
	delete player;
	delete keyControl;
	delete m_EnemyHandler;
	delete ui;
}

void SuperLevel::superLoadContent()
{
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_Level -> loadContent();

	ui = new Ui();
	ui->loadContent();

	m_EnemyHandler -> setUserInterface(ui);

	player = new Player();
	player -> setEnvironmentLevel( m_Level );
	player -> setUserInterface(ui);
	player -> loadContent();

	player -> setEnemyVector( m_EnemyHandler->getEnemyVector( ) );
	player -> setPosition(m_Level -> getPlayerPosition());
	
	keyControl = new KeyboardController(player,StateHandler::getInstance().m_pWindow);
	
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
	keyControl->mouseInput(event);

	ui -> processEvents(event);

	#if (DEBUG)

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		StateHandler::getInstance().addScreen(new TitleScreen());
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		StateHandler::getInstance().addScreen(new SplashScreen());
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		player -> takeDamage(5);
	}
		
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		player -> takeDamage(-5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		player -> modifySouls(5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		player -> modifySouls(-5);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_EnemyHandler -> createEnemy(3);
	}

	#endif

	if (event.type == sf::Event::KeyReleased)
	{
			if(!player->isDoingAction())
			{
			player->changeAnimationToStand();
			}
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
	{
		if(!StateHandler::getInstance().getMenuShield())
		{
			StateHandler::getInstance().m_AudioManager.stopOrResumeMusic();
			StateHandler::getInstance().setMenuShield(true);
		}
	}
}

void SuperLevel::update()
{
	player -> animation();
	player -> update();
	ui -> update();

	if(ui -> hasFaded())
	{
		StateHandler::getInstance().addScreen(new Highscore(player -> getTotalSouls()));
	}

	keyControl->keyboardInput();

	m_EnemyHandler -> update();
	
	m_Viewport.setCenter(player -> getXPosition(), player -> getYPosition());
}

void SuperLevel::superDraw()
{	
	m_Level -> draw();
	m_EnemyHandler -> draw();
	player -> draw();
	ui->draw();
	StateHandler::getInstance().m_pWindow->setView(m_Viewport);
}