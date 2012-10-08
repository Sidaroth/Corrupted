#include "Game.h"
#include <time.h>
#include <stdlib.h>


#include <iostream>

// Lazy initialization
Game* Game::m_gameInstance = NULL;


Game* Game::getInstance()
{
	if( m_gameInstance == NULL )	// Return a new game object if it doesn't exist
	{
		m_gameInstance = new Game();
		return m_gameInstance;
	}
	else							// Else return the already existing object. 
	{
		return m_gameInstance;
	}
}


Game::Game()
{
	m_sTitle = "Corrupted";
	m_bRunning = false;
	m_iScreenWidth = 1360;
	m_iScreenHeight = 768;
	m_iScreenBitColor = 32;
	m_Window.create(sf::VideoMode(m_iScreenWidth, m_iScreenHeight, m_iScreenBitColor), m_sTitle);
}

void Game::start()
{
	if(m_bRunning == false)	
	{
		initialize();
		run();
		deInitialize();
	}
}

void Game::run()
{
	int frames = 0;
	double passedTime = 0;			// *VERY* simple FPS counter.
	time_t previousTime;
	time_t currentTime;

	sf::Text text;

	time (&previousTime);
	
	while ( m_bRunning )
	{
		
		time (&currentTime);
		passedTime = difftime( currentTime, previousTime );
		previousTime = currentTime;
		char fps [10];

		if(passedTime)
		{
			itoa(frames, fps, 10);
			std::cout << "fps: " << frames << std::endl;
			text.setString(fps);
			frames = 0;
		}

		processEvents();
		render(text);
		frames++;

	}
}

void Game::initialize()
{
	m_bRunning = true;
}

void Game::deInitialize()
{
	// uninitialize stuff
	return;
}

void Game::tick()
{

}

void Game::stop()
{
	if ( m_bRunning )
	{
		m_bRunning = false;
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_Window.pollEvent( event ))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
		}
	}

}

void Game::render(sf::Text text)
{
	m_Window.clear();
	m_Window.draw(text);
	m_Window.display();
}