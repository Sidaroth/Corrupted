#include "Game.h"
#include "Player.h"
#include "SplashScreen.h"
#include "StateHandler.h"


Game::Game()
{
	m_sTitle = "Untitled";
	m_shScreenWidth = 800;
	m_shScreenHeight = 600;
	m_shScreenBitColor = 32;
	m_bRunning = false;
	m_BackgroundColor = new sf::Color(0, 0, 0, 255);
	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	//JUST TRYING SOUNDS
	 sf::Music music;
	  // Open it from an audio file
	 if (!music.openFromFile("../../Resources/sounds/sound.wav"))
	 {
		 // error...
		 std::cout << "Error at music loading" << std::endl;

	 }else{

		  // Change some parameters
		 music.setPosition(0, 1, 10); // change its 3D position
		 music.setPitch(2);           // increase the pitch
		 music.setVolume(120);         // reduce the volume
		 music.setLoop(true);         // make it loop

		 // Play it
		 music.play();
		 std::cout << "Playing music" << std::endl;
	 }

	//END JUST TRYING SOUNDS
	//keyControl.loadXML();
}

void Game::initialize(const char* title, short width, short height, short bitPP, bool fullscreen)
{


	m_sTitle = title;
	m_shScreenWidth = width;
	m_shScreenHeight = height;
	m_shScreenBitColor = bitPP;

	m_Window.create(sf::VideoMode(m_shScreenWidth, m_shScreenHeight, m_shScreenBitColor), m_sTitle);
	m_bRunning = true;

	StateHandler::getInstance().initalize();
	StateHandler::getInstance().setStartState(new SplashScreen());
	StateHandler::getInstance().loadContent(&m_Window);


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
			unprocessedSeconds -= secondsPerTick;
			ticked = true;
			tickCount++;

			if(tickCount % 60 == 0)
			{
				_itoa_s(frames, fps, 10);
				std::cout << "fps: " << frames << std::endl;
				frames_per_sec.setString(fps);
				text.setString(fps);
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
	// uninitialize stuff
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
		if(event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			m_Window.close();
			m_bRunning = false;
		}

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