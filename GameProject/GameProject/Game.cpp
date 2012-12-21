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
	m_bRunning = false;
	m_bShield = false;
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
	m_bRunning = true;

	StateHandler::getInstance().initalize();
	StateHandler::getInstance().setStartState(new TitleScreen());
	StateHandler::getInstance().loadContent(&m_Window);

	if( !m_ShieldTexture.loadFromFile("../../Resources/Shield_quit_game.PNG" ) )
	{
		std::cout << "Could not load submit_button.PNG" << std::endl;
	}
	else
	{
		m_ShieldSprite.setTexture( m_ShieldTexture );
		m_ShieldSprite.setPosition( 350, 350 );
	}

	if( !m_ShieldNoTexture.loadFromFile("../../Resources/no.PNG" ) )
	{
		std::cout << "Could not load submit_button.PNG" << std::endl;
	}
	else
	{
		m_ShieldNoSprite.setTexture( m_ShieldNoTexture );
		m_ShieldNoSprite.setPosition( 400, 500 );
	}

	if( !m_ShieldNoPressedTexture.loadFromFile("../../Resources/no_pressed.PNG" ) )
	{
		std::cout << "Could not load submit_button_pressed.PNG" << std::endl;
	}

	if( !m_ShieldYesTexture.loadFromFile("../../Resources/yes.PNG" ) )
	{
		std::cout << "Could not load submit_button.PNG" << std::endl;
	}
	else
	{
		m_ShieldYesSprite.setTexture( m_ShieldYesTexture );
		m_ShieldYesSprite.setPosition( 725, 500 );
	}

	if( !m_ShieldYesPressedTexture.loadFromFile("../../Resources/yes_pressed.PNG" ) )
	{
		std::cout << "Could not load submit_button_pressed.PNG" << std::endl;
	}

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
	if(!m_bShield)
	{
		StateHandler::getInstance().update();
	}
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
			if(!m_bShield)
			{
				m_bShield = true;
			}
		}

		if(!m_bShield)
		{
			StateHandler::getInstance().processEvents(event);
		}

		if(m_bShield)
		{
			if ((	event.mouseMove.x >= m_ShieldNoSprite.getPosition().x && event.mouseMove.x <= m_ShieldNoSprite.getPosition().x + 275  && 
					event.mouseMove.y >= m_ShieldNoSprite.getPosition().y && event.mouseMove.y <= m_ShieldNoSprite.getPosition().y + 100 ))
			{
				m_ShieldNoSprite.setTexture(m_ShieldNoPressedTexture);
			}
			else
			{
				m_ShieldNoSprite.setTexture(m_ShieldNoTexture);
			}

			if(		event.mouseButton.x >=  m_ShieldNoSprite.getPosition().x && event.mouseButton.x <=  m_ShieldNoSprite.getPosition().x + 275 && 
					event.mouseButton.y >=  m_ShieldNoSprite.getPosition().y && event.mouseButton.y <=  m_ShieldNoSprite.getPosition().y + 100 )
			{
				m_bShield = false;
			}

			if ((	event.mouseMove.x >= m_ShieldYesSprite.getPosition().x && event.mouseMove.x <= m_ShieldYesSprite.getPosition().x + 275 && 
					event.mouseMove.y >= m_ShieldYesSprite.getPosition().y && event.mouseMove.y <= m_ShieldYesSprite.getPosition().y + 100 )) 
			{
				m_ShieldYesSprite.setTexture(m_ShieldYesPressedTexture);
			}
			else
			{
				m_ShieldYesSprite.setTexture(m_ShieldYesTexture);
			}

			if(		event.mouseButton.x >=  m_ShieldYesSprite.getPosition().x && event.mouseButton.x <=  m_ShieldYesSprite.getPosition().x+275 && 
					event.mouseButton.y >=  m_ShieldYesSprite.getPosition().y && event.mouseButton.y <=  m_ShieldYesSprite.getPosition().y+100)
			{
				m_Window.close();
				m_bRunning = false;
			}
		}
	}
}

void Game::render()
{
	m_Window.clear(*m_BackgroundColor);
	StateHandler::getInstance().draw();
	m_Window.draw(frames_per_sec);

	if(m_bShield)
	{
		sf::View gameView = m_Window.getView();
		m_Window.setView(m_Window.getDefaultView());
		m_Window.draw(m_ShieldSprite);
		m_Window.draw(m_ShieldNoSprite);
		m_Window.draw(m_ShieldYesSprite);
		m_Window.setView(gameView);
	}

	m_Window.display();
}