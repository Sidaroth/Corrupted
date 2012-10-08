#include "Game.h"


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
	const float FRAMES_PER_SECOND = 60.0f;
	int frames = 0;							// FPS counter & limiter stuff
	float unprocessedSeconds = 0;
	sf::Clock clock;
	sf::Time previousTime;
	sf::Time currentTime;
	sf::Time passedTime;

	
	char fps[10];

	int tickCount = 0;
	bool ticked = false;
	float secondsPerTick = 1 / FRAMES_PER_SECOND;
	sf::Text text;

	
	while ( m_bRunning )
	{
		ticked = false;
		currentTime = clock.getElapsedTime();
		passedTime = currentTime - previousTime;
		previousTime = currentTime;

		unprocessedSeconds += passedTime.asSeconds();

		while( unprocessedSeconds > secondsPerTick )
		{
			tick();
			unprocessedSeconds -= secondsPerTick;
			ticked = true;
			tickCount++;

			if(tickCount % 60 == 0)
			{
				itoa(frames, fps, 10);
				std::cout << "fps: " << frames << std::endl;
				text.setString(fps);
				frames = 0;
			}
		}
			
		
		if(ticked)
		{
			processEvents();
			//update game state here
			render(text);
			frames++;
		}
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
			//m_bRunning = false;
		}
	}

}

void Game::render(sf::Text text)
{
	m_Window.clear();
	m_Window.draw(text);
	m_Window.display();
}