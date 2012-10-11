#include "Game.h"
#include "Player.h"

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
	m_sTitle = "Untitled";
	m_shScreenWidth = 800;
	m_shScreenHeight = 600;
	m_shScreenBitColor = 32;
	m_bRunning = false;
}

void Game::initialize(const char* title, short width = 1336, short height = 768, short bitPP = 32, bool fullscreen = false)
{
	player = new Player();
	player -> loadContent();
	
	m_sTitle = title;
	m_shScreenWidth = width;
	m_shScreenHeight = height;
	m_shScreenBitColor = bitPP;

	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	m_bRunning = true;

	std::cout << "Game initalized" << std::endl;
}

void Game::start()
{
	if(m_bRunning == false)	
	{
		initialize("Corrupted");
	}

	run();
	deInitialize();
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

void Game::deInitialize()
{
	// uninitialize stuff
	return;
}

void Game::update()
{
	
}

void Game::stop()
{
	if ( m_bRunning )
	{
		m_bRunning = false;
	}
}

//void Game::checkKeyboard(){
//	
//	std::string 
//
//		//w a s d, q, e space, mouse 1, mouse 2 
//
//
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
// {
//     // move left...
// }
//
//
//}

void Game::processEvents()
{
	sf::Event event;
	while (m_Window.pollEvent( event ))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			m_bRunning = false;
			break;
		}


		// True is moving up, false down. 
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player -> moveVertical(true);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player -> moveVertical(false);
		}

		// True is moving right, false left. 
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player -> moveHorizontal(true);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player -> moveHorizontal(false);
		}

	}
}

void Game::render(sf::Text text)
{
	m_Window.clear();
	m_Window.draw(text);
	m_Window.draw(player -> getSprite());
	m_Window.display();
}