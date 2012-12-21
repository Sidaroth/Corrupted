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

void EnemyHandler::loadContent(EnvironmentHandler* level)
{
	m_Level = level;
	m_EnemyFactory -> loadContent();
	m_EnemyVector.reserve(25);


	m_EnemySpawnPoints = level->getEnemySpawnPoints();
	numberOfSpawnPoints = m_EnemySpawnPoints->size();
	srand(time(NULL));											//Initialize random seed
	
	createEnemy(20);
}

void EnemyHandler::setUserInterface(Ui* ui)
{
	m_pUserInterface = ui;
}


void EnemyHandler::unloadContent()
{
	for( std::vector<Enemy*>::iterator it = m_EnemyVector.begin(); it != m_EnemyVector.end();)
	{
		delete * it;
		it = m_EnemyVector.erase(it);
	}
}

void EnemyHandler::draw()
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> draw();
	}
}

void EnemyHandler::update(Vector2f* playerPos)
{
	for(unsigned short i = 0; i < m_EnemyVector.size(); i++)
	{
		m_EnemyVector[i] -> update(playerPos);
	}

	if ( (int)spawnTimer.getElapsedTime().asSeconds() % m_waveNumber == 0)
	{
		//newWave();
		++m_waveNumber;
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
	for(int i = 0; i < toBeCreated; i++)
	{	
		m_EnemyVector.push_back(m_EnemyFactory -> createEnemy(m_EnemyFactory -> Skellie));

		if(m_EnemyVector[i] != NULL)
		{
			std::cout << "Enemy created!\n";		
			m_EnemyVector[i] -> loadContent();
		}
		else
		{
			std::cout << "Something went wrong when creating enemy" << std::endl;
			return;
		}

		randomSpawnPoint = m_EnemySpawnPoints->at(rand() % numberOfSpawnPoints);


		m_EnemyVector[i] -> setEnvironmentLevel(m_Level);
		m_EnemyVector[i] -> setUserInterface(m_pUserInterface);
		m_EnemyVector[i] -> setPosition(randomSpawnPoint);
		
		
	}
}

void EnemyHandler::newWave()
{
	
}