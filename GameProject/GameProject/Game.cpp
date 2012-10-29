#include "Game.h"
#include "Player.h"
#include "StateHandler.h"

Game::Game()
{
	m_sTitle = "Untitled";
	m_shScreenWidth = 800;
	m_shScreenHeight = 600;
	m_shScreenBitColor = 32;
	m_bRunning = false;
	m_BackgroundColor = new sf::Color(106, 76, 48, 255);
	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	
	//keyControl.loadXML();
}

void Game::initialize(const char* title, short width, short height, short bitPP, bool fullscreen)
{
	StateHandler::getInstance().initalize();
	StateHandler::getInstance().loadContent();

	player = new Player();
	player -> loadContent();
	keyControl = new KeyboardController(player);
	m_sTitle = title;
	m_shScreenWidth = width;
	m_shScreenHeight = height;
	m_shScreenBitColor = bitPP;

	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	m_bRunning = true;

	std::cout << "Game initialized" << std::endl;
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
			keyControl->checkPressed();
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
	StateHandler::getInstance().update();
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
		
		if((sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			m_Window.close();
			m_bRunning = false;
		}

	//	keyControl->checkPressed();
		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			StateHandler::getInstance().addScreen(new TitleScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			StateHandler::getInstance().addScreen(new SplashScreen);
		}
	}
}

void Game::render()
{
	m_Window.clear(*m_BackgroundColor);
	StateHandler::getInstance().draw(m_Window);
	player->animation();
	m_Window.draw(player -> getSprite());
	m_Window.display();
}