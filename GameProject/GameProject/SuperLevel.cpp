#include "SuperLevel.h"
#include "StateHandler.h"
// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "SplashScreen.h"

SuperLevel::SuperLevel()
{

}

SuperLevel::~SuperLevel()
{
	// Delete all pointers.
	delete m_Level;
	delete player;
	delete keyControl;
	delete m_EnemyHandler;
	delete ui;
}

void SuperLevel::superLoadContent(sf::RenderWindow* window)
{
	m_pWindow = window;
	if(!font.loadFromFile("../../Resources/impact.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	m_Level -> loadContent();

	ui = new Ui();
	ui->loadContent();

	//std::cout << ui << std::endl;
	m_EnemyHandler -> setUserInterface(ui);

	player = new Player();
	player -> setEnvironmentLevel( m_Level );
	player -> setUserInterface(ui);
	player -> loadContent();

	player -> setEnemyVector( m_EnemyHandler->getEnemyVector( ) );
	player -> setPosition(m_Level -> getPlayerPosition());
	
	keyControl = new KeyboardController(player,StateHandler::getInstance().m_pWindow);
	
	m_Viewport.reset(sf::FloatRect(0, 0, 1366, 768));
	m_Viewport.setViewport(sf::FloatRect(0.0f, 0.0f,1.f, 1.0f));
	m_Viewport.setCenter(1366/2, 768/2);
	m_Viewport.zoom(1.5);
}

void SuperLevel::unloadContent()
{

}

void SuperLevel::processEvents(sf::Event event)
{
		keyControl->checkMouse(event);

		ui -> processEvents(event);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			StateHandler::getInstance().addScreen(new TitleScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			StateHandler::getInstance().addScreen(new SplashScreen);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			player -> takeDamage(1);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			player -> takeDamage(-1);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			player -> modifySouls(5);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			player -> modifySouls(-5);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			sf::View tempView = StateHandler::getInstance().m_pWindow -> getView();

			int windowX = tempView.getCenter( ).x - ( tempView.getSize( ).x / 2 );
			int windowY = tempView.getCenter( ).y - ( tempView.getSize( ).y / 2 );

			Vector2f uiPosition((*player -> getPosition()).x, (*player -> getPosition()).y);
			uiPosition.x -= windowX;
			uiPosition.y -= windowY;
			uiPosition.x /= 1.5;
			uiPosition.y /= 1.5;

			ui -> addSouls(123, uiPosition);
		}

		if (event.type == sf::Event::KeyReleased)
		{
			 if(!player->isDoingAction())
			 {
				player->changeAnimationToStand();
			 }
		}
}

void SuperLevel::update()
{
	player -> animation();
	player -> update();
	ui -> update();
	keyControl->checkPressed();
	m_EnemyHandler -> update(player -> getPosition());

	m_Viewport.setCenter(player -> getXPosition(), player -> getYPosition());
}

void SuperLevel::superDraw()
{	
	m_Level -> draw();
	m_EnemyHandler -> draw();
	player -> draw();
	ui->draw();
	StateHandler::getInstance().m_pWindow->setView(m_Viewport);
}