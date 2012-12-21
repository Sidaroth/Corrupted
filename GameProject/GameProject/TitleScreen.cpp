#include "TitleScreen.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "Level1.h"
#include "SplashScreen.h"

TitleScreen::TitleScreen()
{
	menuArray[0] = true;
	menuArray[1] = false;
	menuArray[2] = false;
	currentButton = 0;
}

void TitleScreen::loadContent()
{
	if(!m_menuBackground.loadFromFile("../../Resources/menu.PNG"))
	{
		std::cout << "Could not load background" << std::endl;
	}

	if(!m_startButton.loadFromFile("../../Resources/start.PNG"))
	{
		std::cout << "Could not load startbutton" << std::endl;
	}

	if(!m_startButtonMouseOver.loadFromFile("../../Resources/start_pressed.PNG"))
	{
		std::cout << "Could not load highlighted startbutton" << std::endl;
	}

	if(!m_exitButton.loadFromFile("../../Resources/exit.PNG"))
	{
		std::cout << "Could not load exit button" << std::endl;
	}

	if(!m_exitButtonMouseOver.loadFromFile("../../Resources/exit_pressed.PNG"))
	{
		std::cout << "Could not load highlighted exit button" << std::endl;
	}

	m_menuBackgroundSprite.setTexture(m_menuBackground);
	m_menuBackgroundSprite.setPosition(0, 0);

	m_startButtonSprite.setTexture(m_startButton);
	m_startButtonSprite.setPosition(540, 200);

	m_exitButtonSprite.setTexture(m_exitButton);
	m_exitButtonSprite.setPosition(540, 300);
}

void TitleScreen::unloadContent()
{

}

void TitleScreen::update()
{
	
}

void TitleScreen::processEvents(sf::Event event)
{
	if ((event.mouseMove.x >= m_startButtonSprite.getPosition().x && event.mouseMove.x <= m_startButtonSprite.getPosition().x+270 && 
			event.mouseMove.y >= m_startButtonSprite.getPosition().y && event.mouseMove.y <= m_startButtonSprite.getPosition().y+70) || currentButton == 1) 
	{
		currentButton = 1;
		m_startButtonSprite.setTexture(m_startButtonMouseOver);	
	}
	else
	{
		m_startButtonSprite.setTexture(m_startButton);
	}

	if(event.mouseButton.x >=  m_startButtonSprite.getPosition().x && event.mouseButton.x <=  m_startButtonSprite.getPosition().x+270 && 
			event.mouseButton.y >=  m_startButtonSprite.getPosition().y && event.mouseButton.y <=  m_startButtonSprite.getPosition().y+70)
	{
		StateHandler::getInstance().addScreen(new Level1());
	}
	

	if ((event.mouseMove.x >=  m_exitButtonSprite.getPosition().x && event.mouseMove.x <=  m_exitButtonSprite.getPosition().x+270 && 
			event.mouseMove.y >=  m_exitButtonSprite.getPosition().y && event.mouseMove.y <=  m_exitButtonSprite.getPosition().y+70) || currentButton == 2) 
	{
		currentButton = 2;
		m_exitButtonSprite.setTexture(m_exitButtonMouseOver);	
	}
	else
	{
		m_exitButtonSprite.setTexture(m_exitButton);
	}

	if(event.mouseButton.x >=  m_exitButtonSprite.getPosition().x && event.mouseButton.x <=  m_exitButtonSprite.getPosition().x+270 && 
			event.mouseButton.y >=  m_exitButtonSprite.getPosition().y && event.mouseButton.y <=  m_exitButtonSprite.getPosition().y+70)
	{
		//Exit the game
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (currentButton > 1) 
		{
			currentButton--;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (currentButton < 2) 
		{
			currentButton++;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (currentButton == 1) 
		{
			StateHandler::getInstance().addScreen(new Level1());
		}

		if (currentButton == 2) 
		{
			//Exit game
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		StateHandler::getInstance().addScreen(new Level1());
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		StateHandler::getInstance().addScreen(new SplashScreen());
	}
}

void TitleScreen::draw()
{
	StateHandler::getInstance().m_pWindow->draw(m_menuBackgroundSprite);
	StateHandler::getInstance().m_pWindow->draw(m_startButtonSprite);
	StateHandler::getInstance().m_pWindow->draw(m_exitButtonSprite);
}