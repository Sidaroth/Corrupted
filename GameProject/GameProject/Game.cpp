#include "Game.h"
#include "Player.h"
#include "SplashScreen.h"
#include "Highscore.h"
#include "StateHandler.h"

Game::Game()
{
	m_sTitle = "Corrupted";
	m_shScreenWidth = 800;
	m_shScreenHeight = 600;
	m_shScreenBitColor = 32;
	m_BackgroundColor = new sf::Color(0, 0, 0, 255);
	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
}

void Game::initialize(const char* title, short width, short height, short bitPP, bool fullscreen)
{
	m_sTitle = title;
	m_shScreenWidth = width;
	m_shScreenHeight = height;
	m_shScreenBitColor = bitPP;

	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);

	sf::Image icon;

	if(!icon.loadFromFile("../../Resources/fireball_icon.png"))
	{
		return; // Game broke :<
	}

	icon.createMaskFromColor(sf::Color(0, 0, 0));

	m_Window.setIcon(96, 96, icon.getPixelsPtr());

	StateHandler::getInstance().initalize();
	StateHandler::getInstance().setStartState(new TitleScreen());
	StateHandler::getInstance().loadContent(&m_Window);

	std::cout << "Game initialized" << std::endl;
}

void Game::start()
{
	initialize("Corrupted");

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


	while ( StateHandler::getInstance().getRunning() )
	{
		ticked = false;
		currentTime = clock.getElapsedTime();
		passedTime = currentTime - previousTime;
		previousTime = currentTime;

		unprocessedSeconds += passedTime.asSeconds();

		while( unprocessedSeconds > secondsPerTick )
		{
			unprocessedSeconds -= secondsPerTick;
			ticked = true;
			tickCount++;

			if(tickCount % 60 == 0)
			{
				_itoa_s(frames, fps, 10);
				//std::cout << "fps: " << frames << std::endl;
				frames_per_sec.setString(fps);
				frames = 0;
			}
		}

		if(ticked)
		{
			processEvents();
			update();
			
		}
		render();
		frames++;
	}
}

void Game::deInitialize()
{
	delete m_BackgroundColor;
}

void Game::update()
{
	StateHandler::getInstance().update();
}

void Game::stop()
{
	if ( StateHandler::getInstance().getRunning() )
	{
		StateHandler::getInstance().stopRunning();
	}
}


void Game::processEvents()
{
	sf::Event event;
	while (m_Window.pollEvent( event ))
	{
		StateHandler::getInstance().processEvents(event);
	}
}

void Game::render()
{
	m_Window.clear(*m_BackgroundColor);
	StateHandler::getInstance().draw();
	m_Window.draw(frames_per_sec);

	m_Window.display();
}