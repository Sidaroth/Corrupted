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

void TitleScreen::loadContent(sf::RenderWindow* window)
{
	if(!m_menuBackground.loadFromFile("../../Resources/menuBackground.PNG"))
	{
		std::cout << "Could not load background" << std::endl;
	}

	if(!m_startButton.loadFromFile("../../Resources/startButton.PNG"))
	{
		std::cout << "Could not load startbutton" << std::endl;
	}

	if(!m_startButtonMouseOver.loadFromFile("../../Resources/startButtonMouseOver.PNG"))
	{
		std::cout << "Could not load highlighted startbutton" << std::endl;
	}

	if(!m_exitButton.loadFromFile("../../Resources/exitButton.PNG"))
	{
		std::cout << "Could not load exit button" << std::endl;
	}

	if(!m_exitButtonMouseOver.loadFromFile("../../Resources/exitButtonMouseOver.PNG"))
	{
		std::cout << "Could not load highlighted exit button" << std::endl;
	}

	m_menuBackgroundSprite.setTexture(m_menuBackground);
	m_menuBackgroundSprite.setPosition(0, 0);

	m_startButtonSprite.setTexture(m_startButton);
	m_startButtonSprite.setPosition(100, 100);

	m_exitButtonSprite.setTexture(m_exitButton);
	m_exitButtonSprite.setPosition(100, 300);

	m_pWindow = window;
}

void TitleScreen::unloadContent()
{

}

void TitleScreen::update()
{
	
}

void TitleScreen::processEvents(sf::Event event)
{
	if ((event.mouseMove.x >= 100 && event.mouseMove.x <= 350 && 
			event.mouseMove.y >= 100 && event.mouseMove.y <= 175) || currentButton == 1) 
	{
		currentButton = 1;
		m_startButtonSprite.setTexture(m_startButtonMouseOver);	
	}
	else
	{
		m_startButtonSprite.setTexture(m_startButton);
	}

	if(event.mouseButton.x >= 100 && event.mouseButton.x <= 350 && 
			event.mouseButton.y >= 100 && event.mouseButton.y <= 175)
	{
		StateHandler::getInstance().addScreen(new Level1);
	}
	

	if ((event.mouseMove.x >= 100 && event.mouseMove.x <= 350 && 
			event.mouseMove.y >= 300 && event.mouseMove.y <= 375) || currentButton == 2) 
	{
		currentButton = 2;
		m_exitButtonSprite.setTexture(m_exitButtonMouseOver);	
	}
	else
	{
		m_exitButtonSprite.setTexture(m_exitButton);
	}

	if(event.mouseButton.x >= 100 && event.mouseButton.x <= 350 && 
			event.mouseButton.y >= 300 && event.mouseButton.y <= 375)
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
			StateHandler::getInstance().addScreen(new Level1);
		}

		if (currentButton == 2) 
		{
			//Exit game
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		StateHandler::getInstance().addScreen(new Level1);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		StateHandler::getInstance().addScreen(new SplashScreen);
	}
}

void TitleScreen::draw()
{
	m_pWindow->draw(m_menuBackgroundSprite);
	m_pWindow->draw(m_startButtonSprite);
	m_pWindow->draw(m_exitButtonSprite);
}