#include "StateHandler.h"
#include <assert.h>

StateHandler &StateHandler::getInstance()
{
	static StateHandler instance;
	instance.safe = true;
	return instance;
}

StateHandler::StateHandler()
{
	m_bRunning = true;
	bool m_bQuitShield = false;
	bool m_bMenuShield = false;
}

StateHandler::~StateHandler()
{
	// delete all pointers. 
	// delete currentState;
	// delete newState;
	// delete m_pWindow;
}

void StateHandler::addScreen(GameState *state)
{
	safe = false;
	currentState -> unloadContent();
	//delete currentState;
	
	currentState = state;
	currentState -> loadContent();
	safe = true;
}

void StateHandler::initalize()
{
	currentState = NULL;
}

void StateHandler::setStartState(GameState* state)
{
	currentState = state;
}

void StateHandler::loadContent(sf::RenderWindow* window)
{	
	m_pWindow = window;
	
	if( !m_ShieldQuitTexture.loadFromFile("../../Resources/Shield_quit_game.PNG" ) )
	{
		std::cout << "Could not load Shield_quit_game.PNG" << std::endl;
	}
	else
	{
		m_ShieldSprite.setTexture( m_ShieldQuitTexture );
		m_ShieldSprite.setPosition( 350, 350 );
	}

	if( !m_ShieldMenuTexture.loadFromFile("../../Resources/Shield_main_menu.PNG" ) )
	{
		std::cout << "Could not load Shield_menu_game.PNG" << std::endl;
	}

	if( !m_ShieldNoTexture.loadFromFile("../../Resources/no.PNG" ) )
	{
		std::cout << "Could not load no.PNG" << std::endl;
	}
	else
	{
		m_ShieldNoSprite.setTexture( m_ShieldNoTexture );
		m_ShieldNoSprite.setPosition( 400, 500 );
	}

	if( !m_ShieldNoPressedTexture.loadFromFile("../../Resources/no_pressed.PNG" ) )
	{
		std::cout << "Could not load o_pressed.PNG" << std::endl;
	}

	if( !m_ShieldYesTexture.loadFromFile("../../Resources/yes.PNG" ) )
	{
		std::cout << "Could not load yes.PNG" << std::endl;
	}
	else
	{
		m_ShieldYesSprite.setTexture( m_ShieldYesTexture );
		m_ShieldYesSprite.setPosition( 725, 500 );
	}

	if( !m_ShieldYesPressedTexture.loadFromFile("../../Resources/yes_pressed.PNG" ) )
	{
		std::cout << "Could not load yes_pressed.PNG" << std::endl;
	}

	currentState -> loadContent();
}

void StateHandler::processEvents(sf::Event event)
{
	assert(safe);
	
	if(!m_bMenuShield && !m_bQuitShield)
	{
		currentState -> processEvents(event);
	}

	if(event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !m_bMenuShield))
	{
		if(!m_bQuitShield )
		{
			m_bQuitShield = true;
		}
	}

	if(m_bMenuShield || m_bQuitShield)
	{
		if ((	event.mouseMove.x >= m_ShieldNoSprite.getPosition().x && event.mouseMove.x <= m_ShieldNoSprite.getPosition().x + 275  && 
				event.mouseMove.y >= m_ShieldNoSprite.getPosition().y && event.mouseMove.y <= m_ShieldNoSprite.getPosition().y + 100 ))
		{
			m_ShieldNoSprite.setTexture(m_ShieldNoPressedTexture);
		}
		else
		{
			m_ShieldNoSprite.setTexture(m_ShieldNoTexture);
		}

		if(		event.mouseButton.x >=  m_ShieldNoSprite.getPosition().x && event.mouseButton.x <=  m_ShieldNoSprite.getPosition().x + 275 && 
				event.mouseButton.y >=  m_ShieldNoSprite.getPosition().y && event.mouseButton.y <=  m_ShieldNoSprite.getPosition().y + 100 )
		{
			m_bMenuShield = false;
			m_bQuitShield = false;
		}

		if ((	event.mouseMove.x >= m_ShieldYesSprite.getPosition().x && event.mouseMove.x <= m_ShieldYesSprite.getPosition().x + 275 && 
				event.mouseMove.y >= m_ShieldYesSprite.getPosition().y && event.mouseMove.y <= m_ShieldYesSprite.getPosition().y + 100 )) 
		{
			m_ShieldYesSprite.setTexture(m_ShieldYesPressedTexture);
		}
		else
		{
			m_ShieldYesSprite.setTexture(m_ShieldYesTexture);
		}

		if(		event.mouseButton.x >=  m_ShieldYesSprite.getPosition().x && event.mouseButton.x <=  m_ShieldYesSprite.getPosition().x+275 && 
				event.mouseButton.y >=  m_ShieldYesSprite.getPosition().y && event.mouseButton.y <=  m_ShieldYesSprite.getPosition().y+100)
		{
			if(m_bQuitShield)
			{
				m_pWindow->close();
				StateHandler::getInstance().stopRunning();
			}
			else if(m_bMenuShield)
			{
				sf::View gameView = m_pWindow->getView();
				m_pWindow->setView(m_pWindow->getDefaultView());
				addScreen(new TitleScreen());
				m_bMenuShield = false;
			}
		}
	}
}

void StateHandler::update()
{
	if(!m_bMenuShield)
	{
		currentState -> update();
	}
}

void StateHandler::draw()
{
	
	currentState -> draw();
	if(m_bMenuShield || m_bQuitShield)
	{
		if(m_bMenuShield)
		{
			m_ShieldSprite.setTexture(m_ShieldMenuTexture);
		}
		else
		{
			m_ShieldSprite.setTexture(m_ShieldQuitTexture);
		}
		sf::View gameView = m_pWindow->getView();
		m_pWindow->setView(m_pWindow->getDefaultView());
		m_pWindow->draw(m_ShieldSprite);
		m_pWindow->draw(m_ShieldNoSprite);
		m_pWindow->draw(m_ShieldYesSprite);
		m_pWindow->setView(gameView);
	}
}

void StateHandler::stopRunning()
{
	m_bRunning = false;
}

bool StateHandler::getRunning()
{
	return m_bRunning;
}

void StateHandler::setMenuShield(bool shield)
{
	m_bMenuShield = shield;
}

void StateHandler::setQuitShield(bool shield)
{
	m_bQuitShield = shield;
}

bool StateHandler::getMenuShield()
{
	return m_bMenuShield;
}

bool StateHandler::getQuitShield()
{
	return m_bQuitShield;
}