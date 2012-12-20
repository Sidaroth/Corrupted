#include "SplashScreen.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "Level1.h"

SplashScreen::SplashScreen()
{
	// NATH'N!
}

void SplashScreen::loadContent()
{

	if(!m_splashScreen.loadFromFile("../../Resources/splashScreen.PNG"))
	{
		std::cout << "Could not load splashscreen" << std::endl;
	}

	m_splashScreenSprite.setTexture(m_splashScreen);
	m_splashScreenSprite.setPosition(0, 0);

}

void SplashScreen::unloadContent()
{

}

void SplashScreen::update()
{

}

void SplashScreen::processEvents(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		StateHandler::getInstance().addScreen(new Level1());
	}

	else if(event.type == sf::Event::KeyPressed)
	{
		StateHandler::getInstance().addScreen(new TitleScreen());
	}
}

void SplashScreen::draw()
{
	StateHandler::getInstance().m_pWindow -> draw(m_splashScreenSprite);
}