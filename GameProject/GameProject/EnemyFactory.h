#pragma once

#include "Enemy.h"
#include "Skeleton.h"

/// Factory handling the creation and deletion of all enemies. 
class EnemyFactory
{
protected:

public:
	enum Enemies
	{
		Skellie
		// More soon (tm)..
	};

	Enemy* createEnemy(Enemies enemyType);
};