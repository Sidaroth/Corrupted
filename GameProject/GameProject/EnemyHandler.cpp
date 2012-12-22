#include "EnemyHandler.h"


EnemyHandler::EnemyHandler()
{
	m_EnemyFactory = new EnemyFactory();

	m_waveNumber = 1;
}

EnemyHandler::EnemyHandler(Ui* ui)
{
	m_EnemyFactory = new EnemyFactory();
	m_pUserInterface = ui;

	m_waveNumber = 1;
}

EnemyHandler::~EnemyHandler()
{
	for( std::vector<Enemy*>::iterator it = m_EnemyVector.begin(); it != m_EnemyVector.end();)
	{
		delete * it;
		it = m_EnemyVector.erase(it);
	}
}

void EnemyHandler::loadContent(EnvironmentHandler* level, Vector2f* playerPos)
{
	m_pPlayerPos = playerPos;
	m_Level = level;
	m_EnemyFactory -> loadContent();
	m_EnemyVector.reserve(25);

	m_EnemySpawnPoints = level->getEnemySpawnPoints();
	numberOfSpawnPoints = m_EnemySpawnPoints->size();
	srand(time(NULL));											//Initialize random seed
	
}

void EnemyHandler::setUserInterface(Ui* ui)
{
	m_pUserInterface = ui;
}


void EnemyHandler::unloadContent()
{
	for( std::vector<Enemy*>::iterator it = m_EnemyVector.begin(); it != m_EnemyVector.end();)
	{
		// Call enemies unloadContent here?

		/*delete * it;
		it = m_EnemyVector.erase(it);*/
	}
}

void EnemyHandler::draw()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw();
	}
}

void EnemyHandler::update()
{
	for(std::vector<Enemy*>::iterator enemy = m_EnemyVector.begin(); enemy != m_EnemyVector.end();)
	{
		if((*enemy) -> isDead())
		{
			enemy = m_EnemyVector.erase(enemy);
		}
		else
		{
			(*enemy) -> update();
			++enemy;
		}
	}

	timeInSeconds = (int)spawnTimer.getElapsedTime().asSeconds();

	if ( timeInSeconds > 0 && timeInSeconds % m_waveNumber == 0)
	{
		std::cout << "Timer: " << timeInSeconds << " seconds" << std::endl;
		std::cout << "Creating " << m_waveNumber << " enemies" << std::endl;
		createEnemy(m_waveNumber);
		++m_waveNumber;
		spawnTimer.restart();
	}
}

void EnemyHandler::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	this -> collisionMap = collisionMap;
	m_HorizontalSize = horizontalSize;

	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> setCollisionMap(collisionMap, horizontalSize);
	}
}

std::vector<Enemy*>* EnemyHandler::getEnemyVector( )
{
	return &m_EnemyVector;
}

void EnemyHandler::createEnemy(int toBeCreated)
{
	std::vector<Enemy*>::iterator newlyCreatedEnemy;

	for(int i = 0; i < toBeCreated; i++)
	{	
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie, m_waveNumber));
		newlyCreatedEnemy = m_EnemyVector.end() - 1;

		if((*newlyCreatedEnemy) != NULL)
		{		
			(*newlyCreatedEnemy) -> loadContent(m_pPlayerPos);
		}
		else
		{
			std::cout << "Something went wrong when creating an enemy" << std::endl;
			return;
		}

		randomSpawnPoint = m_EnemySpawnPoints->at(rand() % numberOfSpawnPoints);

		(*newlyCreatedEnemy) -> setEnvironmentLevel(m_Level);
		(*newlyCreatedEnemy) -> setUserInterface(m_pUserInterface);
		(*newlyCreatedEnemy) -> setPosition(randomSpawnPoint);
		(*newlyCreatedEnemy) -> setCollisionMap(collisionMap, m_HorizontalSize);
	}
}

void EnemyHandler::newWave()
{
	
}