#pragma once

#include <time.h>
#include <cstdlib>
#include "Vector2f.h"

#include "EnemyFactory.h"
#include "SFML/Graphics.hpp"
#include "Environment.h"

class EnemyHandler
{
protected:
	EnemyFactory* m_EnemyFactory;
	EnvironmentHandler* m_Level;
	Ui* m_pUserInterface;

	short m_HorizontalSize;	
	std::vector<bool>* collisionMap;
	std::vector<Enemy*> m_EnemyVector;
	Vector2f* m_pPlayerPos;

	std::vector<Vector2f>* m_EnemySpawnPoints;
	Vector2f randomSpawnPoint;
	short numberOfSpawnPoints; 
	int m_waveNumber;

	sf::Clock spawnTimer;
	int timeInSeconds;

public:
	EnemyHandler();
	EnemyHandler(Ui* ui);
	~EnemyHandler();

	void setUserInterface(Ui* ui);
	void loadContent(EnvironmentHandler* level, Vector2f* playerPos);
	void unloadContent();
	void setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize);
	void draw();
	void update();
	std::vector<Enemy*>* getEnemyVector( );

	void createEnemy(int toBeCreated);
	void newWave();
};