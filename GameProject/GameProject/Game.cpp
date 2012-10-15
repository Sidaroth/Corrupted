#include "Game.h"
#include "Player.h"

Game::Game()
{
	m_sTitle = "Untitled";
	m_shScreenWidth = 800;
	m_shScreenHeight = 600;
	m_shScreenBitColor = 32;
	m_bRunning = false;
<<<<<<< HEAD
	m_iScreenWidth = 1360;
	m_iScreenHeight = 768;
	m_iScreenBitColor = 32;
	m_Window.create(sf::VideoMode(m_iScreenWidth, m_iScreenHeight, m_iScreenBitColor), m_sTitle);
	//keyControl.loadXML();
	
	
=======
}

void Game::initialize(const char* title, short width, short height, short bitPP, bool fullscreen)
{
	player = new Player();
	player -> loadContent();
	
	m_sTitle = title;
	m_shScreenWidth = width;
	m_shScreenHeight = height;
	m_shScreenBitColor = bitPP;

	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	m_bRunning = true;

	std::cout << "Game initialized" << std::endl;
>>>>>>> df5d1808936894fa2bdcaea22e7aa5631b900aaf
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
			update();
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
			render();
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
<<<<<<< HEAD
		keyControl.checkPressed();
=======


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

>>>>>>> df5d1808936894fa2bdcaea22e7aa5631b900aaf
	}
}

void Game::render()
{
	m_Window.clear();
	player->animation();
	m_Window.draw(player -> getSprite());
	m_Window.display();
}